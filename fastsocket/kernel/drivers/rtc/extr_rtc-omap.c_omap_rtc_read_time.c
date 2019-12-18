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
struct rtc_time {void* tm_year; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_RTC_DAYS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_HOURS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_MINUTES_REG ; 
 int /*<<< orphan*/  OMAP_RTC_MONTHS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_SECONDS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_YEARS_REG ; 
 int /*<<< orphan*/  bcd2tm (struct rtc_time*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 void* rtc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_wait_not_busy () ; 

__attribute__((used)) static int omap_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	/* we don't report wday/yday/isdst ... */
	local_irq_disable();
	rtc_wait_not_busy();

	tm->tm_sec = rtc_read(OMAP_RTC_SECONDS_REG);
	tm->tm_min = rtc_read(OMAP_RTC_MINUTES_REG);
	tm->tm_hour = rtc_read(OMAP_RTC_HOURS_REG);
	tm->tm_mday = rtc_read(OMAP_RTC_DAYS_REG);
	tm->tm_mon = rtc_read(OMAP_RTC_MONTHS_REG);
	tm->tm_year = rtc_read(OMAP_RTC_YEARS_REG);

	local_irq_enable();

	bcd2tm(tm);
	return 0;
}