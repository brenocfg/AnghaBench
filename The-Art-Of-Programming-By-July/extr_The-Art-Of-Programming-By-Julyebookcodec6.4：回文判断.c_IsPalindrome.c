#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

bool IsPalindrome(const char *s, int n)  
{  
    if (s == NULL || n < 1) return false; // invalid string  
    char *front, *back;  
    front = s; back = s + n - 1; // set front and back to the begin and endof the string  
    while (front < back) {  
        if (*front != *back) return false; // not a palindrome  
        ++front; --back;  
    }  
    return true; // check over, it's a palindrome  
}