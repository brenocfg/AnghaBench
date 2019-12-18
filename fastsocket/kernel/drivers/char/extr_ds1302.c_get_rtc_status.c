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
struct rtc_time {int tm_hour; int tm_min; int tm_sec; int tm_year; int tm_mon; int tm_mday; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_rtc_time (struct rtc_time*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int,int,int) ; 

int
get_rtc_status(char *buf)
{
	char *p;
	struct rtc_time tm;

	p = buf;

	get_rtc_time(&tm);

	/*
	 * There is no way to tell if the luser has the RTC set for local
	 * time or for Universal Standard Time (GMT). Probably local though.
	 */

	p += sprintf(p,
		"rtc_time\t: %02d:%02d:%02d\n"
		"rtc_date\t: %04d-%02d-%02d\n",
		tm.tm_hour, tm.tm_min, tm.tm_sec,
		tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

	return  p - buf;
}