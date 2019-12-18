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
typedef  int time_t ;
struct tm {int tm_sec; int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; } ;

/* Variables and functions */
 int ATOI2 (char*) ; 
 struct tm* localtime (int*) ; 
 int mktime (struct tm*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
str_sec(char *str, time_t *tval)
{
	struct tm *lt;
	char *dot = NULL;

	lt = localtime(tval);
	if ((dot = strchr(str, '.')) != NULL) {
		/*
		 * seconds (.ss)
		 */
		*dot++ = '\0';
		if (strlen(dot) != 2)
			return(-1);
		if ((lt->tm_sec = ATOI2(dot)) > 61)
			return(-1);
	} else
		lt->tm_sec = 0;

	switch (strlen(str)) {
	case 10:
		/*
		 * year (yy)
		 * watch out for year 2000
		 */
		if ((lt->tm_year = ATOI2(str)) < 69)
			lt->tm_year += 100;
		str += 2;
		/* FALLTHROUGH */
	case 8:
		/*
		 * month (mm)
		 * watch out months are from 0 - 11 internally
		 */
		if ((lt->tm_mon = ATOI2(str)) > 12)
			return(-1);
		--lt->tm_mon;
		str += 2;
		/* FALLTHROUGH */
	case 6:
		/*
		 * day (dd)
		 */
		if ((lt->tm_mday = ATOI2(str)) > 31)
			return(-1);
		str += 2;
		/* FALLTHROUGH */
	case 4:
		/*
		 * hour (hh)
		 */
		if ((lt->tm_hour = ATOI2(str)) > 23)
			return(-1);
		str += 2;
		/* FALLTHROUGH */
	case 2:
		/*
		 * minute (mm)
		 */
		if ((lt->tm_min = ATOI2(str)) > 59)
			return(-1);
		break;
	default:
		return(-1);
	}
	/*
	 * convert broken-down time to GMT clock time seconds
	 */
	if ((*tval = mktime(lt)) == -1)
		return(-1);
	return(0);
}