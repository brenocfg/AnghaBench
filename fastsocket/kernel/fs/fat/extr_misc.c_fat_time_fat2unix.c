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
typedef  int u16 ;
typedef  int time_t ;
struct timespec {int tv_sec; int tv_nsec; } ;
struct TYPE_3__ {int /*<<< orphan*/  tz_utc; } ;
struct msdos_sb_info {TYPE_1__ options; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int tz_minuteswest; } ;

/* Variables and functions */
 int DAYS_DELTA ; 
 scalar_t__ IS_LEAP_YEAR (int) ; 
 int SECS_PER_DAY ; 
 int SECS_PER_HOUR ; 
 int SECS_PER_MIN ; 
 int YEAR_2100 ; 
 int* days_in_year ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 TYPE_2__ sys_tz ; 

void fat_time_fat2unix(struct msdos_sb_info *sbi, struct timespec *ts,
		       __le16 __time, __le16 __date, u8 time_cs)
{
	u16 time = le16_to_cpu(__time), date = le16_to_cpu(__date);
	time_t second, day, leap_day, month, year;

	year  = date >> 9;
	month = max(1, (date >> 5) & 0xf);
	day   = max(1, date & 0x1f) - 1;

	leap_day = (year + 3) / 4;
	if (year > YEAR_2100)		/* 2100 isn't leap year */
		leap_day--;
	if (IS_LEAP_YEAR(year) && month > 2)
		leap_day++;

	second =  (time & 0x1f) << 1;
	second += ((time >> 5) & 0x3f) * SECS_PER_MIN;
	second += (time >> 11) * SECS_PER_HOUR;
	second += (year * 365 + leap_day
		   + days_in_year[month] + day
		   + DAYS_DELTA) * SECS_PER_DAY;

	if (!sbi->options.tz_utc)
		second += sys_tz.tz_minuteswest * SECS_PER_MIN;

	if (time_cs) {
		ts->tv_sec = second + (time_cs / 100);
		ts->tv_nsec = (time_cs % 100) * 10000000;
	} else {
		ts->tv_sec = second;
		ts->tv_nsec = 0;
	}
}