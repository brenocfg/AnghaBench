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

int LongestPalindrome(const char *s, int n)  
{
    int i, j, max;  
    if (s == 0 || n < 1) return 0;  
    max = 0;  
    for (i = 0; i < n; ++i) { // i is the middle point of the palindrome  
        for (j = 0; (i-j >= 0) && (i+j < n); ++j) // if the lengthof the palindrome is odd  
            if (s[i-j] != s[i+j]) break;  
        if (j*2+1 > max) max = j * 2 + 1;  
        for (j = 0; (i-j >= 0) && (i+j+1 < n); ++j) // for theeven case  
            if (s[i-j] != s[i+j+1]) break;  
        if (j*2+2 > max) max = j * 2 + 2;  
    }  
    return max;  
}