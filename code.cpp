//Proxy Design Pattern

#include <iostream>

class EmployeeTable
{
    public:
    virtual void create(std::string client, int empId) = 0;
    virtual void del(std::string client, int empId) = 0;
    virtual void get(std::string client, int empId) = 0;
};

class EmployeeTableImpl : public EmployeeTable
{
    protected:
    virtual void create(std::string client, int empId) override {
        std::cout << "Employee data created in table" << "\n";
    }
    
    virtual void del(std::string client, int empId) override {
        std::cout << "Employee data deleted from table" << "\n";
    }
    
    virtual void get(std::string client, int empId) override {
        std::cout << "Employee Data: " << empId << "\n";
    }
};

class EmployeeTableProxy : public EmployeeTable
{
    EmployeeTable *handler;
    
    public:
    EmployeeTableProxy(EmployeeTableImpl *handle) : handler{handle}
    {}
    
    void create(std::string client, int empId) override {
        if(client == "ADMIN") {
            handler->create(client,empId);
            return;
        }
        throw "Access Denied!!";
    }
    
    void del(std::string client, int empId) override {
        if(client == "ADMIN") {
            handler->del(client,empId);
            return;
        }
        throw "Access Denied!!";
    }
    
    void get(std::string client, int empId) override {
        if(client == "ADMIN" || client == "USER") {
            handler->get(client,empId);
            return;
        }
        throw "Access Denied!!";
    }
};

int main()
{
    try {
        EmployeeTable *handle = new EmployeeTableProxy(new EmployeeTableImpl);
        handle->create("ADMIN", 52834);
        handle->del("ADMIN", 52834);
        //handle->create("USER", 52835);
        handle->get("ADMIN", 52834);
        handle->get("USER", 52834);
    }
    
    catch(const char *message) {
        std::cout << message << "\n";
        std::cout << "Process Exited Abnormally" << "\n";
    }
    
    std::cout << "Main Finished" << "\n";
    
    /*EmployeeTable *handle1 = new EmployeeTableImpl;
    handle1->create("ADMIN", 52834);
    handle1->create("USER", 52835);*/
    return 0;
}