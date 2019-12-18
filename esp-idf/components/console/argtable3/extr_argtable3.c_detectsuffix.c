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
 scalar_t__ toupper (int) ; 

__attribute__((used)) static int detectsuffix(const char *str, const char *suffix)
{
    /* scan pairwise through strings until mismatch detected */
    while( toupper((int) *str) == toupper((int) *suffix) )
    {
        /* printf("'%c' '%c'\n", *str, *suffix); */

        /* return 1 (success) if match persists until the string terminator */
        if (*str == '\0')
            return 1;

        /* next chars */
        str++;
        suffix++;
    }
    /* printf("'%c' '%c' mismatch\n", *str, *suffix); */

    /* return 0 (fail) if the matching did not consume the entire suffix */
    if (*suffix != 0)
        return 0;   /* failed to consume entire suffix */

    /* skip any remaining whitespace in str */
    while (isspace((int) *str))
        str++;

    /* return 1 (success) if we have reached end of str else return 0 (fail) */
    return (*str == '\0') ? 1 : 0;
}