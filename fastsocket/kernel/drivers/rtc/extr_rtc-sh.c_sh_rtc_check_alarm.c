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
struct rtc_time {int tm_year; int tm_mon; int tm_mday; int tm_wday; int tm_hour; int tm_min; int tm_sec; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int sh_rtc_check_alarm(struct rtc_time *tm)
{
	/*
	 * The original rtc says anything > 0xc0 is "don't care" or "match
	 * all" - most users use 0xff but rtc-dev uses -1 for the same thing.
	 * The original rtc doesn't support years - some things use -1 and
	 * some 0xffff. We use -1 to make out tests easier.
	 */
	if (tm->tm_year == 0xffff)
		tm->tm_year = -1;
	if (tm->tm_mon >= 0xff)
		tm->tm_mon = -1;
	if (tm->tm_mday >= 0xff)
		tm->tm_mday = -1;
	if (tm->tm_wday >= 0xff)
		tm->tm_wday = -1;
	if (tm->tm_hour >= 0xff)
		tm->tm_hour = -1;
	if (tm->tm_min >= 0xff)
		tm->tm_min = -1;
	if (tm->tm_sec >= 0xff)
		tm->tm_sec = -1;

	if (tm->tm_year > 9999 ||
		tm->tm_mon >= 12 ||
		tm->tm_mday == 0 || tm->tm_mday >= 32 ||
		tm->tm_wday >= 7 ||
		tm->tm_hour >= 24 ||
		tm->tm_min >= 60 ||
		tm->tm_sec >= 60)
		return -EINVAL;

	return 0;
}