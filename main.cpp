#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

const int month_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Date
{
private:
    int _year;
    int _month;
    int _day;
    
    // Check if a year is a leap year
    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    
    // Check if a date is valid
    bool isValidDate(int year, int month, int day) const {
        if (year < 1900 || year > 2030 || month < 1 || month > 12 || day < 1)
            return false;
        
        if (month == 2) {
            if (isLeapYear(year))
                return day <= 29;
            else
                return day <= 28;
        }
        
        // For other months, use the month_days array
        int days[] = {0, 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return day <= days[month];
    }
    
    // Get the number of days in a month
    int daysInMonth(int year, int month) const {
        if (month == 2 && isLeapYear(year))
            return 29;
        return month_days[month];
    }
    
    // Convert date to total days since a reference point
    long long toDays() const {
        long long days = 0;
        // Add days for years
        for (int y = 1900; y < _year; y++) {
            days += isLeapYear(y) ? 366 : 365;
        }
        // Add days for months
        for (int m = 1; m < _month; m++) {
            days += daysInMonth(_year, m);
        }
        // Add days
        days += _day - 1;  // Subtract 1 because 1900-1-1 should be day 0
        return days;
    }
    
    // Convert total days to date
    void fromDays(long long totalDays) {
        _year = 1900;
        // Add 1 to totalDays because we subtracted 1 in toDays
        totalDays += 1;
        
        while (totalDays > (isLeapYear(_year) ? 366 : 365)) {
            totalDays -= (isLeapYear(_year) ? 366 : 365);
            _year++;
        }
        
        _month = 1;
        while (totalDays > daysInMonth(_year, _month)) {
            totalDays -= daysInMonth(_year, _month);
            _month++;
        }
        
        _day = totalDays;
    }

public:
    // Constructor
    Date() {
        _year = 1900;
        _month = 1;
        _day = 1;
    }
    
    Date(int yy, int mm, int dd) {
        if (isValidDate(yy, mm, dd)) {
            _year = yy;
            _month = mm;
            _day = dd;
        } else {
            _year = 1900;
            _month = 1;
            _day = 1;
        }
    }
    
    // Pre-increment: ++d
    Date& operator++() {
        long long days = toDays() + 1;
        fromDays(days);
        return *this;
    }
    
    // Post-increment: d++
    Date operator++(int) {
        Date temp = *this;
        ++(*this);
        return temp;
    }
    
    // Pre-decrement: --d
    Date& operator--() {
        long long days = toDays() - 1;
        fromDays(days);
        return *this;
    }
    
    // Post-decrement: d--
    Date operator--(int) {
        Date temp = *this;
        --(*this);
        return temp;
    }
    
    // Add days: d + days
    Date operator+(int days) const {
        Date result = *this;
        long long totalDays = result.toDays() + days;
        result.fromDays(totalDays);
        return result;
    }
    
    // Subtract days: d - days
    Date operator-(int days) const {
        Date result = *this;
        long long totalDays = result.toDays() - days;
        result.fromDays(totalDays);
        return result;
    }
    
    // Compare: d1 < d2
    bool operator<(const Date& other) const {
        if (_year != other._year)
            return _year < other._year;
        if (_month != other._month)
            return _month < other._month;
        return _day < other._day;
    }
    
    // Subtract dates: d1 - d2 (absolute difference in days)
    int operator-(const Date& other) const {
        long long days1 = toDays();
        long long days2 = other.toDays();
        long long diff = days1 - days2;
        return diff > 0 ? diff : -diff;
    }
    
    // Output operator
    friend ostream& operator<<(ostream& os, const Date& date) {
        os << date._year << "-" << date._month << "-" << date._day;
        return os;
    }
    
    // Output function (backup)
    void out() {
        cout << _year << "-" << _month << "-" << _day << endl;
    }
};

void Test()
{
    int op;
    cin >> op;
    int yy, mm, dd;
    if (op == 1 || op == 0)
    {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
        //d0.out(); d1.out(); d2.out();
    }
    if (op == 2 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i=0;i<5;++i) cout << ++d0 << endl; //(++d0).out();
        for (int i=0;i<5;++i) cout << d0++ << endl; //(d0++).out();
        for (int i=0;i<5;++i) cout << d0-- << endl; //(d0--).out();
        for (int i=0;i<2;++i) cout << --d0 << endl; //(--d0).out();
        cout << d0 << endl;
        //d0.out();
    }
    if (op == 3 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << endl;
        // (d0+100).out();
        cout << d0 - 1000 << endl;
        // (d0-1000).out();
    }
    if (op == 4 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << endl;
    }
    if (op == 5 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << d0 - d1 << endl;
    }
}

int main()
{
    Test();
    return 0;
}