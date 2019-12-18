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

__attribute__((used)) static int
uqd_oct(u_quad_t val, char *str, int len, int term)
{
	char *pt;

	/*
	 * term selects the appropriate character(s) for the end of the string
	 */
	pt = str + len - 1;
	switch(term) {
	case 3:
		*pt-- = '\0';
		break;
	case 2:
		*pt-- = ' ';
		*pt-- = '\0';
		break;
	case 1:
		*pt-- = ' ';
		break;
	case 0:
	default:
		*pt-- = '\0';
		*pt-- = ' ';
		break;
	}

	/*
	 * convert and blank pad if there is space
	 */
	while (pt >= str) {
		*pt-- = '0' + (char)(val & 0x7);
		if ((val = val >> 3) == 0)
			break;
	}

	while (pt >= str)
		*pt-- = '0';
	if (val != (u_quad_t)0)
		return(-1);
	return(0);
}