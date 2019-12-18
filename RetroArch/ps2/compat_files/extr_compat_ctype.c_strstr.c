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
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,scalar_t__) ; 

char *strstr(const char *string, const char *substring)
{
    char *strpos;

    if (string == 0)
        return 0;

    if (strlen(substring) == 0)
        return (char *)string;

    strpos = (char *)string;

    while (*strpos != 0) {
        if (strncmp(strpos, substring, strlen(substring)) == 0)
            return strpos;

        strpos++;
    }

    return 0;
}