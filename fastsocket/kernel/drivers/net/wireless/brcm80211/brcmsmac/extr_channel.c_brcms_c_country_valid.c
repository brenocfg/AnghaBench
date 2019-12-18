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
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static bool brcms_c_country_valid(const char *ccode)
{
	/*
	 * only allow ascii alpha uppercase for the first 2
	 * chars.
	 */
	if (!((0x80 & ccode[0]) == 0 && ccode[0] >= 0x41 && ccode[0] <= 0x5A &&
	      (0x80 & ccode[1]) == 0 && ccode[1] >= 0x41 && ccode[1] <= 0x5A))
		return false;

	/*
	 * do not match ISO 3166-1 user assigned country codes
	 * that may be in the driver table
	 */
	if (!strcmp("AA", ccode) ||        /* AA */
	    !strcmp("ZZ", ccode) ||        /* ZZ */
	    ccode[0] == 'X' ||             /* XA - XZ */
	    (ccode[0] == 'Q' &&            /* QM - QZ */
	     (ccode[1] >= 'M' && ccode[1] <= 'Z')))
		return false;

	if (!strcmp("NA", ccode))
		return false;

	return true;
}