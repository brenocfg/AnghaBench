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
 scalar_t__ strchr (char const*,char) ; 

char *strtok(char *strToken, const char *strDelimit)
{
    static char *start;
    static char *end;

    if (strToken != NULL)
        start = strToken;
    else {
        if (*end == 0)
            return 0;

        start = end;
    }

    if (*start == 0)
        return 0;

    // Strip out any leading delimiters
    while (strchr(strDelimit, *start)) {
        // If a character from the delimiting string
        // then skip past it

        start++;

        if (*start == 0)
            return 0;
    }

    if (*start == 0)
        return 0;

    end = start;

    while (*end != 0) {
        if (strchr(strDelimit, *end)) {
            // if we find a delimiting character
            // before the end of the string, then
            // terminate the token and move the end
            // pointer to the next character
            *end = 0;
            end++;
            return start;
        }
        end++;
    }

    // reached the end of the string before finding a delimiter
    // so dont move on to the next character
    return start;
}