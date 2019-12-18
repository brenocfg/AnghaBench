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
 scalar_t__ LEAPS_THRU_END_OF (long) ; 
 unsigned long SECS_PER_DAY ; 
 long SECS_PER_HOUR ; 
 long SECS_PER_MINUTE ; 
 size_t __isleap (long) ; 

__attribute__((used)) static void unmktime(unsigned long time, long offset,
		     int *yearp, int *monp, int *dayp,
		     int *hourp, int *minp, int *secp)
{
        /* How many days come before each month (0-12).  */
	static const unsigned short int __mon_yday[2][13] =
	{
		/* Normal years.  */
		{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
		/* Leap years.  */
		{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
	};
	long int days, rem, y, wday, yday;
	const unsigned short int *ip;

	days = time / SECS_PER_DAY;
	rem = time % SECS_PER_DAY;
	rem += offset;
	while (rem < 0) {
		rem += SECS_PER_DAY;
		--days;
	}
	while (rem >= SECS_PER_DAY) {
		rem -= SECS_PER_DAY;
		++days;
	}
	*hourp = rem / SECS_PER_HOUR;
	rem %= SECS_PER_HOUR;
	*minp = rem / SECS_PER_MINUTE;
	*secp = rem % SECS_PER_MINUTE;
	/* January 1, 1970 was a Thursday. */
	wday = (4 + days) % 7; /* Day in the week. Not currently used */
	if (wday < 0) wday += 7;
	y = 1970;

#define DIV(a, b) ((a) / (b) - ((a) % (b) < 0))
#define LEAPS_THRU_END_OF(y) (DIV (y, 4) - DIV (y, 100) + DIV (y, 400))
#define __isleap(year)	\
  ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))

	while (days < 0 || days >= (__isleap (y) ? 366 : 365))
	{
		/* Guess a corrected year, assuming 365 days per year.  */
		long int yg = y + days / 365 - (days % 365 < 0);

		/* Adjust DAYS and Y to match the guessed year.  */
		days -= ((yg - y) * 365
			 + LEAPS_THRU_END_OF (yg - 1)
			 - LEAPS_THRU_END_OF (y - 1));
		y = yg;
	}
	*yearp = y - 1900;
	yday = days; /* day in the year.  Not currently used. */
	ip = __mon_yday[__isleap(y)];
	for (y = 11; days < (long int) ip[y]; --y)
		continue;
	days -= ip[y];
	*monp = y;
	*dayp = days + 1; /* day in the month */
	return;
}