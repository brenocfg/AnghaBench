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
struct stmp3xxx_rtc_data {scalar_t__ io; } ;
struct rtc_wkalrm {int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HW_RTC_ALARM ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,scalar_t__) ; 
 struct stmp3xxx_rtc_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_tm_to_time (int /*<<< orphan*/ *,unsigned long*) ; 

__attribute__((used)) static int stmp3xxx_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alm)
{
	unsigned long t;
	struct stmp3xxx_rtc_data *rtc_data = dev_get_drvdata(dev);

	rtc_tm_to_time(&alm->time, &t);
	__raw_writel(t, rtc_data->io + HW_RTC_ALARM);
	return 0;
}