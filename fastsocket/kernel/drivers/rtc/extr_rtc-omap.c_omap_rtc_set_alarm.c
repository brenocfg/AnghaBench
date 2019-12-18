#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_year; } ;
struct rtc_wkalrm {scalar_t__ enabled; TYPE_1__ time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM_DAYS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM_HOURS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM_MINUTES_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM_MONTHS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM_SECONDS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM_YEARS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_INTERRUPTS_IT_ALARM ; 
 int /*<<< orphan*/  OMAP_RTC_INTERRUPTS_REG ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  rtc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_wait_not_busy () ; 
 int /*<<< orphan*/  rtc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tm2bcd (TYPE_1__*) ; 

__attribute__((used)) static int omap_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alm)
{
	u8 reg;

	if (tm2bcd(&alm->time) < 0)
		return -EINVAL;

	local_irq_disable();
	rtc_wait_not_busy();

	rtc_write(alm->time.tm_year, OMAP_RTC_ALARM_YEARS_REG);
	rtc_write(alm->time.tm_mon, OMAP_RTC_ALARM_MONTHS_REG);
	rtc_write(alm->time.tm_mday, OMAP_RTC_ALARM_DAYS_REG);
	rtc_write(alm->time.tm_hour, OMAP_RTC_ALARM_HOURS_REG);
	rtc_write(alm->time.tm_min, OMAP_RTC_ALARM_MINUTES_REG);
	rtc_write(alm->time.tm_sec, OMAP_RTC_ALARM_SECONDS_REG);

	reg = rtc_read(OMAP_RTC_INTERRUPTS_REG);
	if (alm->enabled)
		reg |= OMAP_RTC_INTERRUPTS_IT_ALARM;
	else
		reg &= ~OMAP_RTC_INTERRUPTS_IT_ALARM;
	rtc_write(reg, OMAP_RTC_INTERRUPTS_REG);

	local_irq_enable();

	return 0;
}