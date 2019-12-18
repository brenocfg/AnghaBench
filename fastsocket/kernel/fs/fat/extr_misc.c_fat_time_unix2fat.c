#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int time_t ;
struct timespec {int tv_sec; int tv_nsec; } ;
struct TYPE_3__ {int /*<<< orphan*/  tz_utc; } ;
struct msdos_sb_info {TYPE_1__ options; } ;
typedef  scalar_t__ __le16 ;
struct TYPE_4__ {int tz_minuteswest; } ;

/* Variables and functions */
 int DAYS_DELTA ; 
 scalar_t__ IS_LEAP_YEAR (int) ; 
 int SECS_PER_DAY ; 
 int SECS_PER_HOUR ; 
 int SECS_PER_MIN ; 
 int UNIX_SECS_1980 ; 
 int UNIX_SECS_2108 ; 
 int YEAR_2100 ; 
 scalar_t__ cpu_to_le16 (int) ; 
 int* days_in_year ; 
 TYPE_2__ sys_tz ; 

void fat_time_unix2fat(struct msdos_sb_info *sbi, struct timespec *ts,
		       __le16 *time, __le16 *date, u8 *time_cs)
{
	time_t second = ts->tv_sec;
	time_t day, leap_day, month, year;

	if (!sbi->options.tz_utc)
		second -= sys_tz.tz_minuteswest * SECS_PER_MIN;

	/* Jan 1 GMT 00:00:00 1980. But what about another time zone? */
	if (second < UNIX_SECS_1980) {
		*time = 0;
		*date = cpu_to_le16((0 << 9) | (1 << 5) | 1);
		if (time_cs)
			*time_cs = 0;
		return;
	}
#if BITS_PER_LONG == 64
	if (second >= UNIX_SECS_2108) {
		*time = cpu_to_le16((23 << 11) | (59 << 5) | 29);
		*date = cpu_to_le16((127 << 9) | (12 << 5) | 31);
		if (time_cs)
			*time_cs = 199;
		return;
	}
#endif

	day = second / SECS_PER_DAY - DAYS_DELTA;
	year = day / 365;
	leap_day = (year + 3) / 4;
	if (year > YEAR_2100)		/* 2100 isn't leap year */
		leap_day--;
	if (year * 365 + leap_day > day)
		year--;
	leap_day = (year + 3) / 4;
	if (year > YEAR_2100)		/* 2100 isn't leap year */
		leap_day--;
	day -= year * 365 + leap_day;

	if (IS_LEAP_YEAR(year) && day == days_in_year[3]) {
		month = 2;
	} else {
		if (IS_LEAP_YEAR(year) && day > days_in_year[3])
			day--;
		for (month = 1; month < 12; month++) {
			if (days_in_year[month + 1] > day)
				break;
		}
	}
	day -= days_in_year[month];

	*time = cpu_to_le16(((second / SECS_PER_HOUR) % 24) << 11
			    | ((second / SECS_PER_MIN) % 60) << 5
			    | (second % SECS_PER_MIN) >> 1);
	*date = cpu_to_le16((year << 9) | (month << 5) | (day + 1));
	if (time_cs)
		*time_cs = (ts->tv_sec & 1) * 100 + ts->tv_nsec / 10000000;
}