// assignment 2 - Yash Bhatt
//
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct STUDENT_DATA
{
    std::string firstName;
    std::string lastName;
#ifdef PRE_RELEASE
    std::string email;
#endif
};

std::vector<STUDENT_DATA> LoadStudents(const std::string& filename)
{
    std::vector<STUDENT_DATA> students;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string first, last;
        std::getline(ss, first, ',');
        std::getline(ss, last);
        STUDENT_DATA s{ first, last };
        students.push_back(s);
    }
    return students;
}

    #ifdef PRE_RELEASE
    void LoadEmails(const std::string& filename, std::vector<STUDENT_DATA>& students)
    {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string first, last, email;
        std::getline(ss, first, ',');
        std::getline(ss, last, ',');
        std::getline(ss, email);

        for (auto& s : students)
        {
            if (s.firstName == first && s.lastName == last)
            {
                s.email = email;
                break;
            }
          }
        }
    }
    #endif

    int main()
    {
    #ifdef PRE_RELEASE
        std::cout << "Running PRE-RELEASE build" << std::endl;
    #else
        std::cout << "Running STANDARD build" << std::endl;
    #endif

        std::vector<STUDENT_DATA> students = LoadStudents("StudentData.txt");

    #ifdef PRE_RELEASE
        LoadEmails("StudentData_Emails.txt", students);
    #endif

    #ifdef _DEBUG
        for (const auto& s : students)
        {
            std::cout << s.firstName << " " << s.lastName;
    #ifdef PRE_RELEASE
            std::cout << " <" << s.email << ">";
    #endif
            std::cout << std::endl;
        }
    #endif

        return 0;

    }
