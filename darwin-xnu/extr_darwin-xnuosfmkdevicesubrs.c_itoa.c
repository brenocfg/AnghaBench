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

char *
itoa(
	int	num,
	char	*str)
{
        char    digits[11];
        char *dp;
        char *cp = str;

        if (num == 0) {
            *cp++ = '0';
        }
        else {
            dp = digits;
            while (num) {
                *dp++ = '0' + num % 10;
                num /= 10;
            }
            while (dp != digits) {
                *cp++ = *--dp;
            }
        }
        *cp++ = '\0';

	return str;
}