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

int
uqd_asc(u_quad_t val, char *str, int len, int base)
{
	char *pt;
	u_quad_t digit;

	/*
	 * WARNING str is not '\0' terminated by this routine
	 */
	pt = str + len - 1;

	/*
	 * do a tailwise conversion (start at right most end of string to place
	 * least significant digit). Keep shifting until conversion value goes
	 * to zero (all digits were converted)
	 */
	if (base == HEX) {
		while (pt >= str) {
			if ((digit = (val & 0xf)) < 10)
				*pt-- = '0' + (char)digit;
			else
				*pt-- = 'a' + (char)(digit - 10);
			if ((val = (val >> 4)) == (u_quad_t)0)
				break;
		}
	} else {
		while (pt >= str) {
			*pt-- = '0' + (char)(val & 0x7);
			if ((val = (val >> 3)) == (u_quad_t)0)
				break;
		}
	}

	/*
	 * pad with leading ascii ZEROS. We return -1 if we ran out of space.
	 */
	while (pt >= str)
		*pt-- = '0';
	if (val != (u_quad_t)0)
		return(-1);
	return(0);
}