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
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HW_RTC_SECONDS ; 
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 struct stmp3xxx_rtc_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_time_to_tm (int /*<<< orphan*/ ,struct rtc_time*) ; 
 int /*<<< orphan*/  stmp3xxx_wait_time (struct stmp3xxx_rtc_data*) ; 

__attribute__((used)) static int stmp3xxx_rtc_gettime(struct device *dev, struct rtc_time *rtc_tm)
{
	struct stmp3xxx_rtc_data *rtc_data = dev_get_drvdata(dev);

	stmp3xxx_wait_time(rtc_data);
	rtc_time_to_tm(__raw_readl(rtc_data->io + HW_RTC_SECONDS), rtc_tm);
	return 0;
}