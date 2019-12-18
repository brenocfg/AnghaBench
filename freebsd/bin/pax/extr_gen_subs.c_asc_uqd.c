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
typedef  int u_quad_t ;

/* Variables and functions */
 int HEX ; 

u_quad_t
asc_uqd(char *str, int len, int base)
{
	char *stop;
	u_quad_t tval = 0;

	stop = str + len;

	/*
	 * skip over leading blanks and zeros
	 */
	while ((str < stop) && ((*str == ' ') || (*str == '0')))
		++str;

	/*
	 * for each valid digit, shift running value (tval) over to next digit
	 * and add next digit
	 */
	if (base == HEX) {
		while (str < stop) {
			if ((*str >= '0') && (*str <= '9'))
				tval = (tval << 4) + (*str++ - '0');
			else if ((*str >= 'A') && (*str <= 'F'))
				tval = (tval << 4) + 10 + (*str++ - 'A');
			else if ((*str >= 'a') && (*str <= 'f'))
				tval = (tval << 4) + 10 + (*str++ - 'a');
			else
				break;
		}
	} else {
 		while ((str < stop) && (*str >= '0') && (*str <= '7'))
			tval = (tval << 3) + (*str++ - '0');
	}
	return(tval);
}