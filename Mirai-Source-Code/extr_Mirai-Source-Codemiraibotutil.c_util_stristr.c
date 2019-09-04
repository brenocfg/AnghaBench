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
 int util_strlen (char*) ; 

int util_stristr(char *haystack, int haystack_len, char *str)
{
    char *ptr = haystack;
    int str_len = util_strlen(str);
    int match_count = 0;

    while (haystack_len-- > 0)
    {
        char a = *ptr++;
        char b = str[match_count];
        a = a >= 'A' && a <= 'Z' ? a | 0x60 : a;
        b = b >= 'A' && b <= 'Z' ? b | 0x60 : b;

        if (a == b)
        {
            if (++match_count == str_len)
                return (ptr - haystack);
        }
        else
            match_count = 0;
    }

    return -1;
}