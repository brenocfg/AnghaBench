#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int tm_sec; int tm_hour; int tm_min; } ;
struct rtc_wkalrm {int /*<<< orphan*/  enabled; TYPE_1__ time; } ;
struct rtc_time {int dummy; } ;
struct rtc_plat_data {int /*<<< orphan*/  g_rtc_alarm; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RTC_ALM_BIT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mxc_rtc_irq_enable (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtc_plat_data* platform_get_drvdata (struct platform_device*) ; 
 int rtc_update_alarm (struct device*,TYPE_1__*) ; 
 int rtc_valid_tm (TYPE_1__*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int mxc_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtc_plat_data *pdata = platform_get_drvdata(pdev);
	int ret;

	if (rtc_valid_tm(&alrm->time)) {
		if (alrm->time.tm_sec > 59 ||
		    alrm->time.tm_hour > 23 ||
		    alrm->time.tm_min > 59)
			return -EINVAL;

		ret = rtc_update_alarm(dev, &alrm->time);
	} else {
		ret = rtc_valid_tm(&alrm->time);
		if (ret)
			return ret;

		ret = rtc_update_alarm(dev, &alrm->time);
	}

	if (ret)
		return ret;

	memcpy(&pdata->g_rtc_alarm, &alrm->time, sizeof(struct rtc_time));
	mxc_rtc_irq_enable(dev, RTC_ALM_BIT, alrm->enabled);

	return 0;
}