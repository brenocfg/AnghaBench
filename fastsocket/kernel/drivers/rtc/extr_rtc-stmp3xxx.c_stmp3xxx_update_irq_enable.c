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
 int /*<<< orphan*/  BM_RTC_CTRL_ONEMSEC_IRQ_EN ; 
 scalar_t__ HW_RTC_CTRL ; 
 struct stmp3xxx_rtc_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  stmp3xxx_clearl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stmp3xxx_setl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int stmp3xxx_update_irq_enable(struct device *dev, unsigned int enabled)
{
	struct stmp3xxx_rtc_data *rtc_data = dev_get_drvdata(dev);

	if (enabled)
		stmp3xxx_setl(BM_RTC_CTRL_ONEMSEC_IRQ_EN,
				rtc_data->io + HW_RTC_CTRL);
	else
		stmp3xxx_clearl(BM_RTC_CTRL_ONEMSEC_IRQ_EN,
				rtc_data->io + HW_RTC_CTRL);
	return 0;
}