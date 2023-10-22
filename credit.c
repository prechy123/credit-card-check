#include <stdio.h>

typedef char * string;


int get_digit_count(long n);
int calc_checksum(long card_number, int digit_count);
string get_card_type(long card_number, int digit_count, int checkresult);

int main(void)
{
    // prompt for input
    long card_number;
    printf("Enter credit card: ");
    scanf("%li", &card_number);

    // digit count
    int digit_count = get_digit_count(card_number);

    // calculate checksum
    int checkresult = calc_checksum(card_number, digit_count);

    // check for credit card length and starting digits
    string card_type = get_card_type(card_number, digit_count, checkresult);

    // print card type or invalid
    printf("%s\n", card_type);
}

int get_digit_count(long n)
{
    long temp = n;
    int digitcount = 0;
    while (temp != 0)
    {
        temp /= 10;
        digitcount++;
    }
    return digitcount;
}

int calc_checksum(long card_number, int digit_count)
{
    long even_divider = 10;
    long old_divider = 1;
    int looptimes = digit_count / 2;
    int added_multiplied_even_position = 0;
    int added_odd_position = 0;
    int total;
    for (int i = 0; i <= looptimes; i++)
    {
        // even position digits
        long even_current_digit = (card_number / even_divider) % 10;
        even_current_digit *= 2;
        if (even_current_digit / 10 != 0)
        {
            int even_current_digit1 = even_current_digit / 10;
            int even_current_digit2 = even_current_digit % 10;
            added_multiplied_even_position += even_current_digit1 + even_current_digit2;
        }
        else
        {
            added_multiplied_even_position += even_current_digit;
        }
        even_divider *= 100;

        // old position digits
        int old_current_digit = (card_number / old_divider) % 10;
        added_odd_position += old_current_digit;
        old_divider *= 100;
    }

    total = added_multiplied_even_position + added_odd_position;
    if (total % 10 == 0)
    {
        return total;
    }
    else
    {
        return 99; // thatis it is wrong
    }
}

string get_card_type(long card_number, int digit_count, int checkresult)
{
    if (checkresult == 99)
    {
        return "INVALID"; // checking if it is 99 from calc_checksum
    }
    else if (digit_count == 15)
    {
        int first = (card_number / 100000000000000) % 10;
        int second = (card_number / 10000000000000) % 10;
        if (first == 3 && (second == 3 || second == 7))
        {
            return "AMEX";
        }
        else
        {
            return "INVALID";
        }
    }
    else if (digit_count == 16)
    {
        int first = (card_number / 1000000000000000) % 10;
        int second = (card_number / 100000000000000) % 10;
        if (first == 5 && (second == 1 || second == 2 || second == 3 || second == 4 || second == 5))
        {
            return "MASTERCARD";
        }
        else if (first == 4)
        {
            return "VISA";
        }
        else
        {
            return "INVALID";
        }
    }
    else if (digit_count == 13)
    {
        int first = (card_number / 1000000000000) % 10;
        if (first == 4)
        {
            return "VISA";
        }
        else
        {
            return "INVALID";
        }
    }
    else
    {
        return "INVALID";
    }
}