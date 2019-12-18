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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_year; int tm_wday; int tm_mon; int tm_mday; } ;

/* Variables and functions */
 unsigned int AT91_RTC_CENT ; 
 unsigned int AT91_RTC_DATE ; 
 unsigned int AT91_RTC_DAY ; 
 unsigned int AT91_RTC_HOUR ; 
 unsigned int AT91_RTC_MIN ; 
 unsigned int AT91_RTC_MONTH ; 
 unsigned int AT91_RTC_SEC ; 
 unsigned int AT91_RTC_YEAR ; 
 unsigned int at91_sys_read (unsigned int) ; 
 int bcd2bin (unsigned int) ; 

__attribute__((used)) static void at91_rtc_decodetime(unsigned int timereg, unsigned int calreg,
				struct rtc_time *tm)
{
	unsigned int time, date;

	/* must read twice in case it changes */
	do {
		time = at91_sys_read(timereg);
		date = at91_sys_read(calreg);
	} while ((time != at91_sys_read(timereg)) ||
			(date != at91_sys_read(calreg)));

	tm->tm_sec  = bcd2bin((time & AT91_RTC_SEC) >> 0);
	tm->tm_min  = bcd2bin((time & AT91_RTC_MIN) >> 8);
	tm->tm_hour = bcd2bin((time & AT91_RTC_HOUR) >> 16);

	/*
	 * The Calendar Alarm register does not have a field for
	 * the year - so these will return an invalid value.  When an
	 * alarm is set, at91_alarm_year wille store the current year.
	 */
	tm->tm_year  = bcd2bin(date & AT91_RTC_CENT) * 100;	/* century */
	tm->tm_year += bcd2bin((date & AT91_RTC_YEAR) >> 8);	/* year */

	tm->tm_wday = bcd2bin((date & AT91_RTC_DAY) >> 21) - 1;	/* day of the week [0-6], Sunday=0 */
	tm->tm_mon  = bcd2bin((date & AT91_RTC_MONTH) >> 16) - 1;
	tm->tm_mday = bcd2bin((date & AT91_RTC_DATE) >> 24);
}