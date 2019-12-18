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
typedef  char* u_int ;
typedef  char* off_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  HN_AUTOSCALE ; 
 int HN_B ; 
 int HN_DECIMAL ; 
 int HN_NOSPACE ; 
 int /*<<< orphan*/  HUMANVALSTR_LEN ; 
 scalar_t__ f_humanval ; 
 scalar_t__ f_thousands ; 
 int /*<<< orphan*/  humanize_number (char*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char const*,char*,char*) ; 

__attribute__((used)) static void
printsize(size_t width, off_t bytes)
{

	if (f_humanval) {
		/*
		 * Reserve one space before the size and allocate room for
		 * the trailing '\0'.
		 */
		char buf[HUMANVALSTR_LEN - 1 + 1];

		humanize_number(buf, sizeof(buf), (int64_t)bytes, "",
		    HN_AUTOSCALE, HN_B | HN_NOSPACE | HN_DECIMAL);
		(void)printf("%*s ", (u_int)width, buf);
	} else if (f_thousands) {		/* with commas */
		/* This format assignment needed to work round gcc bug. */
		const char *format = "%*j'd ";
		(void)printf(format, (u_int)width, bytes);
	} else
		(void)printf("%*jd ", (u_int)width, bytes);
}