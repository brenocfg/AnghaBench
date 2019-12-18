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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_wday; int tm_mday; int tm_mon; int tm_year; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_ADDR_DATE ; 
 int /*<<< orphan*/  RTC_ADDR_DAY ; 
 int /*<<< orphan*/  RTC_ADDR_HOUR ; 
 int /*<<< orphan*/  RTC_ADDR_MIN ; 
 int /*<<< orphan*/  RTC_ADDR_MON ; 
 int /*<<< orphan*/  RTC_ADDR_SEC ; 
 int /*<<< orphan*/  RTC_ADDR_YEAR ; 
 int bin2bcd (int) ; 
 int ds1302_readbyte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds1302_writebyte (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ds1302_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	/* Stop RTC */
	ds1302_writebyte(RTC_ADDR_SEC, ds1302_readbyte(RTC_ADDR_SEC) | 0x80);

	ds1302_writebyte(RTC_ADDR_SEC, bin2bcd(tm->tm_sec));
	ds1302_writebyte(RTC_ADDR_MIN, bin2bcd(tm->tm_min));
	ds1302_writebyte(RTC_ADDR_HOUR, bin2bcd(tm->tm_hour));
	ds1302_writebyte(RTC_ADDR_DAY, bin2bcd(tm->tm_wday));
	ds1302_writebyte(RTC_ADDR_DATE, bin2bcd(tm->tm_mday));
	ds1302_writebyte(RTC_ADDR_MON, bin2bcd(tm->tm_mon + 1));
	ds1302_writebyte(RTC_ADDR_YEAR, bin2bcd(tm->tm_year % 100));

	/* Start RTC */
	ds1302_writebyte(RTC_ADDR_SEC, ds1302_readbyte(RTC_ADDR_SEC) & ~0x80);

	return 0;
}