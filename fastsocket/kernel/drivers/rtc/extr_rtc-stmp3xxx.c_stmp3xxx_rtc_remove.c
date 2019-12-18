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
struct stmp3xxx_rtc_data {scalar_t__ io; int /*<<< orphan*/  rtc; int /*<<< orphan*/  irq_1msec; int /*<<< orphan*/  irq_alarm; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BM_RTC_CTRL_ALARM_IRQ_EN ; 
 int BM_RTC_CTRL_ONEMSEC_IRQ_EN ; 
 scalar_t__ HW_RTC_CTRL ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct stmp3xxx_rtc_data*) ; 
 struct stmp3xxx_rtc_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rtc_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmp3xxx_clearl (int,scalar_t__) ; 

__attribute__((used)) static int stmp3xxx_rtc_remove(struct platform_device *pdev)
{
	struct stmp3xxx_rtc_data *rtc_data = platform_get_drvdata(pdev);

	if (!rtc_data)
		return 0;

	stmp3xxx_clearl(BM_RTC_CTRL_ONEMSEC_IRQ_EN | BM_RTC_CTRL_ALARM_IRQ_EN,
			rtc_data->io + HW_RTC_CTRL);
	free_irq(rtc_data->irq_alarm, &pdev->dev);
	free_irq(rtc_data->irq_1msec, &pdev->dev);
	rtc_device_unregister(rtc_data->rtc);
	iounmap(rtc_data->io);
	kfree(rtc_data);

	return 0;
}