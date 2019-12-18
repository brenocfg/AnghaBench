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
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HW_RTC_SECONDS ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,scalar_t__) ; 
 struct stmp3xxx_rtc_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  stmp3xxx_wait_time (struct stmp3xxx_rtc_data*) ; 

__attribute__((used)) static int stmp3xxx_rtc_set_mmss(struct device *dev, unsigned long t)
{
	struct stmp3xxx_rtc_data *rtc_data = dev_get_drvdata(dev);

	__raw_writel(t, rtc_data->io + HW_RTC_SECONDS);
	stmp3xxx_wait_time(rtc_data);
	return 0;
}