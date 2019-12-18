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
typedef  char u8 ;
struct rtc_time {int tm_year; char tm_sec; char tm_min; char tm_hour; char tm_mday; char tm_mon; } ;
typedef  int /*<<< orphan*/  ce_time ;

/* Variables and functions */
 char bin2bcd (char) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int signal_ce_msg (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mf_set_rtc(struct rtc_time *tm)
{
	char ce_time[12];
	u8 day, mon, hour, min, sec, y1, y2;
	unsigned year;

	year = 1900 + tm->tm_year;
	y1 = year / 100;
	y2 = year % 100;

	sec = tm->tm_sec;
	min = tm->tm_min;
	hour = tm->tm_hour;
	day = tm->tm_mday;
	mon = tm->tm_mon + 1;

	sec = bin2bcd(sec);
	min = bin2bcd(min);
	hour = bin2bcd(hour);
	mon = bin2bcd(mon);
	day = bin2bcd(day);
	y1 = bin2bcd(y1);
	y2 = bin2bcd(y2);

	memset(ce_time, 0, sizeof(ce_time));
	ce_time[3] = 0x41;
	ce_time[4] = y1;
	ce_time[5] = y2;
	ce_time[6] = sec;
	ce_time[7] = min;
	ce_time[8] = hour;
	ce_time[10] = day;
	ce_time[11] = mon;

	return signal_ce_msg(ce_time, NULL);
}