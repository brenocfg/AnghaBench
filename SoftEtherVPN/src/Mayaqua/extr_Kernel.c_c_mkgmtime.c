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
typedef  int /*<<< orphan*/  time_64t ;
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; int tm_yday; unsigned int tm_wday; scalar_t__ tm_isdst; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_TM (int,int,int) ; 
 int TM_HOUR_MAX ; 
 int TM_MDAY_MAX ; 
 int TM_MIN_MAX ; 
 size_t TM_MON_MAX ; 
 int TM_SEC_MAX ; 
 int TM_YEAR_MAX ; 
 scalar_t__ leap (int) ; 
 int monthlen (int,int) ; 
 scalar_t__ nleap (int) ; 
 int* ydays ; 

time_64t c_mkgmtime(struct tm *tm)
{
	int years, months, days, hours, minutes, seconds;

	years = tm->tm_year + 1900;   /* year - 1900 -> year */
	months = tm->tm_mon;          /* 0..11 */
	days = tm->tm_mday - 1;       /* 1..31 -> 0..30 */
	hours = tm->tm_hour;          /* 0..23 */
	minutes = tm->tm_min;         /* 0..59 */
	seconds = tm->tm_sec;         /* 0..61 in ANSI C. */

	ADJUST_TM(seconds, minutes, 60);
	ADJUST_TM(minutes, hours, 60);
	ADJUST_TM(hours, days, 24);
	ADJUST_TM(months, years, 12);
	if (days < 0)
		do {
			if (--months < 0) {
				--years;
				months = 11;
			}
			days += monthlen(months, years);
		} while (days < 0);
	else
		while (days >= monthlen(months, years)) {
			days -= monthlen(months, years);
			if (++months >= 12) {
				++years;
				months = 0;
			}
		}

		/* Restore adjusted values in tm structure */
		tm->tm_year = years - 1900;
		tm->tm_mon = months;
		tm->tm_mday = days + 1;
		tm->tm_hour = hours;
		tm->tm_min = minutes;
		tm->tm_sec = seconds;

		/* Set `days' to the number of days into the year. */
		days += ydays[months] + (months > 1 && leap (years));
		tm->tm_yday = days;

		/* Now calculate `days' to the number of days since Jan 1, 1970. */
		days = (unsigned)days + 365 * (unsigned)(years - 1970) +
			(unsigned)(nleap (years));
		tm->tm_wday = ((unsigned)days + 4) % 7; /* Jan 1, 1970 was Thursday. */
		tm->tm_isdst = 0;

		if (years < 1970)
			return (time_64t)-1;

#if (defined(TM_YEAR_MAX) && defined(TM_MON_MAX) && defined(TM_MDAY_MAX))
#if (defined(TM_HOUR_MAX) && defined(TM_MIN_MAX) && defined(TM_SEC_MAX))
		if (years > TM_YEAR_MAX ||
			(years == TM_YEAR_MAX &&
			(tm->tm_yday > ydays[TM_MON_MAX] + (TM_MDAY_MAX - 1) +
			(TM_MON_MAX > 1 && leap (TM_YEAR_MAX)) ||
			(tm->tm_yday == ydays[TM_MON_MAX] + (TM_MDAY_MAX - 1) +
			(TM_MON_MAX > 1 && leap (TM_YEAR_MAX)) &&
			(hours > TM_HOUR_MAX ||
			(hours == TM_HOUR_MAX &&
			(minutes > TM_MIN_MAX ||
			(minutes == TM_MIN_MAX && seconds > TM_SEC_MAX) )))))))
			return (time_64t)-1;
#endif
#endif

		return (time_64t)(86400L * (unsigned long)(unsigned)days +
			3600L * (unsigned long)hours +
			(unsigned long)(60 * minutes + seconds));
}