#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {long hour; long minute; long second; long year; long month; long day; } ;
typedef  TYPE_1__ efi_time_t ;

/* Variables and functions */
 scalar_t__ LEAPS_THRU_END_OF (long) ; 
 unsigned long SECS_PER_DAY ; 
 long SECS_PER_HOUR ; 
 size_t __isleap (long) ; 

int
offtime (unsigned long t, efi_time_t *tp)
{
	const unsigned short int __mon_yday[2][13] =
	{
		/* Normal years.  */
		{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
		/* Leap years.  */
		{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
	};
	long int days, rem, y;
	const unsigned short int *ip;

	days = t / SECS_PER_DAY;
	rem = t % SECS_PER_DAY;
	while (rem < 0) {
		rem += SECS_PER_DAY;
		--days;
	}
	while (rem >= SECS_PER_DAY) {
		rem -= SECS_PER_DAY;
		++days;
	}
	tp->hour = rem / SECS_PER_HOUR;
	rem %= SECS_PER_HOUR;
	tp->minute = rem / 60;
	tp->second = rem % 60;
	/* January 1, 1970 was a Thursday.  */
	y = 1970;

#	define DIV(a, b) ((a) / (b) - ((a) % (b) < 0))
#	define LEAPS_THRU_END_OF(y) (DIV (y, 4) - DIV (y, 100) + DIV (y, 400))
#	define __isleap(year) \
	  ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))

	while (days < 0 || days >= (__isleap (y) ? 366 : 365)) {
		/* Guess a corrected year, assuming 365 days per year.  */
		long int yg = y + days / 365 - (days % 365 < 0);

		/* Adjust DAYS and Y to match the guessed year.  */
		days -= ((yg - y) * 365 + LEAPS_THRU_END_OF (yg - 1)
			 - LEAPS_THRU_END_OF (y - 1));
		y = yg;
	}
	tp->year = y;
	ip = __mon_yday[__isleap(y)];
	for (y = 11; days < (long int) ip[y]; --y)
		continue;
	days -= ip[y];
	tp->month = y + 1;
	tp->day = days + 1;
	return 1;
}