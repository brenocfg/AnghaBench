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
 scalar_t__ isspace (int) ; 
 long strtol (char const*,char**,int) ; 
 scalar_t__ toupper (int) ; 

__attribute__((used)) static long int strtol0X(const char * str,
                         const char * *endptr,
                         char X,
                         int base)
{
    long int val;               /* stores result */
    int s = 1;                    /* sign is +1 or -1 */
    const char *ptr = str;        /* ptr to current position in str */

    /* skip leading whitespace */
    while (isspace((int) *ptr))
        ptr++;
    /* printf("1) %s\n",ptr); */

    /* scan optional sign character */
    switch (*ptr)
    {
    case '+':
        ptr++;
        s = 1;
        break;
    case '-':
        ptr++;
        s = -1;
        break;
    default:
        s = 1;
        break;
    }
    /* printf("2) %s\n",ptr); */

    /* '0X' prefix */
    if ((*ptr++) != '0')
    {
        /* printf("failed to detect '0'\n"); */
        *endptr = str;
        return 0;
    }
    /* printf("3) %s\n",ptr); */
    if (toupper((int) *ptr++) != toupper((int) X))
    {
        /* printf("failed to detect '%c'\n",X); */
        *endptr = str;
        return 0;
    }
    /* printf("4) %s\n",ptr); */

    /* attempt conversion on remainder of string using strtol() */
    val = strtol(ptr, (char * *)endptr, base);
    if (*endptr == ptr)
    {
        /* conversion failed */
        *endptr = str;
        return 0;
    }

    /* success */
    return s * val;
}