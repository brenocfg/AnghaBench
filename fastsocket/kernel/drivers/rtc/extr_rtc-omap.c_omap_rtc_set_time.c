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
struct rtc_time {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_year; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OMAP_RTC_DAYS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_HOURS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_MINUTES_REG ; 
 int /*<<< orphan*/  OMAP_RTC_MONTHS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_SECONDS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_YEARS_REG ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  rtc_wait_not_busy () ; 
 int /*<<< orphan*/  rtc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tm2bcd (struct rtc_time*) ; 

__attribute__((used)) static int omap_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	if (tm2bcd(tm) < 0)
		return -EINVAL;
	local_irq_disable();
	rtc_wait_not_busy();

	rtc_write(tm->tm_year, OMAP_RTC_YEARS_REG);
	rtc_write(tm->tm_mon, OMAP_RTC_MONTHS_REG);
	rtc_write(tm->tm_mday, OMAP_RTC_DAYS_REG);
	rtc_write(tm->tm_hour, OMAP_RTC_HOURS_REG);
	rtc_write(tm->tm_min, OMAP_RTC_MINUTES_REG);
	rtc_write(tm->tm_sec, OMAP_RTC_SECONDS_REG);

	local_irq_enable();

	return 0;
}