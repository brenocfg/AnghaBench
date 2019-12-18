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
typedef  int u8 ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; scalar_t__ tm_isdst; scalar_t__ tm_yday; scalar_t__ tm_wday; } ;

/* Variables and functions */
 int bcd2bin (int) ; 
 int /*<<< orphan*/  mf_set_rtc (struct rtc_time*) ; 

__attribute__((used)) static int rtc_set_tm(int rc, u8 *ce_msg, struct rtc_time *tm)
{
	tm->tm_wday = 0;
	tm->tm_yday = 0;
	tm->tm_isdst = 0;
	if (rc) {
		tm->tm_sec = 0;
		tm->tm_min = 0;
		tm->tm_hour = 0;
		tm->tm_mday = 15;
		tm->tm_mon = 5;
		tm->tm_year = 52;
		return rc;
	}

	if ((ce_msg[2] == 0xa9) ||
	    (ce_msg[2] == 0xaf)) {
		/* TOD clock is not set */
		tm->tm_sec = 1;
		tm->tm_min = 1;
		tm->tm_hour = 1;
		tm->tm_mday = 10;
		tm->tm_mon = 8;
		tm->tm_year = 71;
		mf_set_rtc(tm);
	}
	{
		u8 year = ce_msg[5];
		u8 sec = ce_msg[6];
		u8 min = ce_msg[7];
		u8 hour = ce_msg[8];
		u8 day = ce_msg[10];
		u8 mon = ce_msg[11];

		sec = bcd2bin(sec);
		min = bcd2bin(min);
		hour = bcd2bin(hour);
		day = bcd2bin(day);
		mon = bcd2bin(mon);
		year = bcd2bin(year);

		if (year <= 69)
			year += 100;

		tm->tm_sec = sec;
		tm->tm_min = min;
		tm->tm_hour = hour;
		tm->tm_mday = day;
		tm->tm_mon = mon;
		tm->tm_year = year;
	}

	return 0;
}