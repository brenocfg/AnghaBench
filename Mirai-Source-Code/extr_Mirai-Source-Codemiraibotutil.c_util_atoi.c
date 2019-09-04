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
 unsigned long LONG_MAX ; 
 unsigned long LONG_MIN ; 
 scalar_t__ util_isalpha (int) ; 
 scalar_t__ util_isdigit (int) ; 
 scalar_t__ util_isspace (int) ; 
 scalar_t__ util_isupper (int) ; 

int util_atoi(char *str, int base)
{
	unsigned long acc = 0;
	int c;
	unsigned long cutoff;
	int neg = 0, any, cutlim;

	do {
		c = *str++;
	} while (util_isspace(c));
	if (c == '-') {
		neg = 1;
		c = *str++;
	} else if (c == '+')
		c = *str++;

	cutoff = neg ? -(unsigned long)LONG_MIN : LONG_MAX;
	cutlim = cutoff % (unsigned long)base;
	cutoff /= (unsigned long)base;
	for (acc = 0, any = 0;; c = *str++) {
		if (util_isdigit(c))
			c -= '0';
		else if (util_isalpha(c))
			c -= util_isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
            
		if (c >= base)
			break;

		if (any < 0 || acc > cutoff || acc == cutoff && c > cutlim)
			any = -1;
		else {
			any = 1;
			acc *= base;
			acc += c;
		}
	}
	if (any < 0) {
		acc = neg ? LONG_MIN : LONG_MAX;
	} else if (neg)
		acc = -acc;
	return (acc);
}