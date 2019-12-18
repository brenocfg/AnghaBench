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
struct rtc_wkalrm {int /*<<< orphan*/  enabled; int /*<<< orphan*/  time; } ;
struct pl031_local {scalar_t__ base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTC_MIS ; 
 scalar_t__ RTC_MR ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 struct pl031_local* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_tm_to_time (int /*<<< orphan*/ *,unsigned long*) ; 

__attribute__((used)) static int pl031_set_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct pl031_local *ldata = dev_get_drvdata(dev);
	unsigned long time;

	rtc_tm_to_time(&alarm->time, &time);

	__raw_writel(time, ldata->base + RTC_MR);
	__raw_writel(!alarm->enabled, ldata->base + RTC_MIS);

	return 0;
}