#include <bits/stdc++.h>
using namespace std;
class Date
{
    private:
    int year;
    int month;
    int day;
    public:
    Date (int _year,int _month,int _day)
    {
        year = _year;
        month = _month;
        day = _day;
    }
    void show() const
    {
        printf("%d年%02d月%02d日",year,month,day);
    }
};
class Staff
{
    protected:
    string name;
    string sex;
    Date B_date;
    Date E_date;
    string dept;
    double salary;
    public:
    Staff(string _name,char _sex,Date &B,Date &E,string _dept,double _salary):B_date(B),E_date(E)
    {
        name = _name;
        if(_sex=='f')
            sex = "女";
        else if (_sex == 'm')
            sex = "男";
        dept = _dept;
        salary = _salary;
    }
    string getName ()
    {
        return name;
    }
    virtual void show()
    {
        cout<<"姓名:"<<name<<endl;
        cout<<"性别:"<<sex<<endl;
        cout<<"出生日期:";
        B_date.show();
        cout<<endl;
        cout<<"入职日期:";
        E_date.show();
        cout<<endl;
        cout<<"部门:"<<dept<<endl;
        cout<<"工资:"<<salary<<endl;
        
    }
};
class Teacher:virtual public Staff
{
    protected:
    string title;
    public:
    Teacher(string _name,char _sex,Date b,Date e,string _dept,double _salary,string _title):Staff(_name,_sex,b,e,_dept,_salary)
    {
        title = _title;
    }
    void show()
    {
        cout<<"专任教师"<<endl;
        Staff::show();
        cout<<"职称:"<<title<<endl;
    }
};
class Ad_Staff:virtual public Staff
{
    protected:
    string postation;
    public:
    Ad_Staff(string _name,char _sex,Date b,Date e,string _dept,double _salary,string _postation):Staff(_name,_sex,b,e,_dept,_salary)
    {
    postation = _postation;
    }
    void show()
    {
    cout<<"行政人员"<<endl;
    Staff::show();
    cout<<"职位:"<<postation<<endl;
    }
};
class Tea_Ad_Staff:public Teacher , public Ad_Staff
{
    public:
    string s1,s2;
    Tea_Ad_Staff(string _name,char _sex,Date b,Date e,string _dept,double _salary,string _title,string _postation):Staff(_name,_sex,b,e,_dept,_salary),Teacher(_name,_sex,b,e,_dept,_salary,_title),Ad_Staff(_name,_sex,b,e,_dept,_salary,_postation)
    {
        s1=_title;
        s2=_postation;
    }
    void show()
    {
    cout<<"双挑人员"<<endl;
    Staff::show();
    cout<<"职称:"<<s1<<endl;
    cout<<"职位:"<<s2<<endl;
    }
};
class O_Teacher:public Teacher{
    protected:
    string company;
    public:
    O_Teacher(string _name,char _sex,Date& b,Date& e,string _dept,double _salary,string _title,string _company)
        :Staff(_name,_sex,b,e,_dept,_salary),Teacher(_name,_sex,b,e,_dept,_salary,_title)
    {
        company=_company;
    }
    void show()
    {
        cout<<"外聘教师"<<endl;
        Staff::show();
        cout<<"职称:"<<title<<endl;
        cout<<"单位:"<<company<<endl;
    }
};
class Staff_list
{
    private:
    int num;
    Staff *L[100];
    public:
    Staff_list()
    {
        num=0;
    };
    void Add(Teacher& t)
    {
        L[num++]=new Teacher(t);
    }
    void Add(Ad_Staff& as)
    {
        L[num++]=new Ad_Staff(as);
    }
    void Add(Tea_Ad_Staff& tas)
    {
        L[num++]=new Tea_Ad_Staff(tas);
    }
    void Add(O_Teacher& ot)
    {
        L[num++]=new O_Teacher(ot);
    }
    void printAll()
    {
        cout<<"所有员工信息如下:"<<endl;
        for(int i=0;i<num;i++)
        {
            
            cout<<"No "<<i+1<<" ";
            L[i]->show();
            cout<<endl;
        }
    }
    void Find(string name)
{
    int i,number=0;
    for (i = 0; i < num; ++i) 
    {
        if (L[i]->getName() == name) 
        {
            number=1;
            cout<<name<<"的信息如下:"<<endl;
            L[i]->show();
        }
        else if(i==num-1&&number==0)
        {
            cout<<"查无此人!"<<endl;
        }
    }
}
    
};
int main()
{
    int n;
    //     姓名 部门 职称   职位      单位
    string name,dept,title,postation,company;
    //sex性别
    char sex,c;
    int byear,bmonth,bday,eyear,emonth,eday;    
    double salary;
    int choice;
    Staff_list L;
    cout<<"欢迎使用员工信息系统！"<<endl<<"请先输入员工信息："<<endl<<"说明：输入1以添加教师，输入2以添加行政人员，输入3以添加双挑人员，输入4以添加外聘教师，输入0以结束输入。"<<endl;
    while(cin>>n && n!=0)
    {
        cin>>name>>sex;        
        cin>>byear>>c>>bmonth>>c>>bday;
        cin>>eyear>>c>>emonth>>c>>eday;
        cin>>dept>>salary;
        // e_date入职日期 b_date 出生日期
        Date e_date(eyear,emonth,eday),b_date(byear,bmonth,bday);
        switch(n)
        {
            //添加教师 
            case 1:{                            
                cin>>title;
                Teacher t(name,sex,b_date,e_date,dept,salary,title);
                L.Add(t);
                break;                
            }
            //添加行政人员 
            case 2:{
                cin>>postation;
                Ad_Staff as(name,sex,b_date,e_date,dept,salary,postation);
                L.Add(as);
                break;                
            }
            //添加双挑人员 
            case 3:{
                cin>>postation;
                cin>>title;
                Tea_Ad_Staff tas(name,sex,b_date,e_date,dept,salary,postation,title);
                L.Add(tas);
                break;                
            }
            //添加外聘教师 
            case 4:
            {
                cin>>title;
                cin>>company;
                O_Teacher ot(name,sex,b_date,e_date,dept,salary,title,company);
                L.Add(ot);
                break;    
            }
        }
    }
    do
    {
        cout<<"-----主菜单-----"<<endl;
        cout<<"请选择操作："<<endl;
        cout<<"1. 输出所有员工信息"<<endl;
        cout<<"2. 查找某个员工信息"<<endl;
        cout<<"3. 退出"<<endl;
        cin>>choice;
        switch (choice)
        {
            case 1: // 输出所有员工信息
            {
                L.printAll();
                break;
            }
            case 2: // 查找某个员工信息
            {
                string namefind;
                cout<<"请输入要查找的员工姓名："<<endl;
                cin>>namefind;
                L.Find(namefind);
                break;
                }
            case 3: // 退出
            {
                cout<<"感谢您使用本员工信息系统！程序已退出。"<<endl;
                break;
            }
            default:
            {
                cout<<"输入有误，请重新输入。"<<endl;
                break;
            }
        }
    } while (choice != 3);
    return 0;
}
