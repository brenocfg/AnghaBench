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
struct stmp3xxx_rtc_data {scalar_t__ io; int /*<<< orphan*/  rtc; void* irq_alarm; void* irq_1msec; scalar_t__ irq_count; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int BM_RTC_CTRL_ALARM_IRQ_EN ; 
 int BM_RTC_CTRL_ONEMSEC_IRQ_EN ; 
 int BM_RTC_PERSISTENT0_ALARM_EN ; 
 int BM_RTC_PERSISTENT0_ALARM_WAKE ; 
 int BM_RTC_PERSISTENT0_ALARM_WAKE_EN ; 
 int BM_RTC_STAT_RTC_PRESENT ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HW_RTC_CTRL ; 
 scalar_t__ HW_RTC_PERSISTENT0 ; 
 scalar_t__ HW_RTC_STAT ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_DISABLED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free_irq (void*,int /*<<< orphan*/ *) ; 
 scalar_t__ ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct stmp3xxx_rtc_data*) ; 
 struct stmp3xxx_rtc_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stmp3xxx_rtc_data*) ; 
 int request_irq (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  rtc_device_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmp3xxx_clearl (int,scalar_t__) ; 
 int /*<<< orphan*/  stmp3xxx_reset_block (scalar_t__,int) ; 
 int /*<<< orphan*/  stmp3xxx_rtc_interrupt ; 
 int /*<<< orphan*/  stmp3xxx_rtc_ops ; 

__attribute__((used)) static int stmp3xxx_rtc_probe(struct platform_device *pdev)
{
	struct stmp3xxx_rtc_data *rtc_data;
	struct resource *r;
	int err;

	rtc_data = kzalloc(sizeof *rtc_data, GFP_KERNEL);
	if (!rtc_data)
		return -ENOMEM;

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!r) {
		dev_err(&pdev->dev, "failed to get resource\n");
		err = -ENXIO;
		goto out_free;
	}

	rtc_data->io = ioremap(r->start, resource_size(r));
	if (!rtc_data->io) {
		dev_err(&pdev->dev, "ioremap failed\n");
		err = -EIO;
		goto out_free;
	}

	rtc_data->irq_alarm = platform_get_irq(pdev, 0);
	rtc_data->irq_1msec = platform_get_irq(pdev, 1);

	if (!(__raw_readl(HW_RTC_STAT + rtc_data->io) &
			BM_RTC_STAT_RTC_PRESENT)) {
		dev_err(&pdev->dev, "no device onboard\n");
		err = -ENODEV;
		goto out_remap;
	}

	stmp3xxx_reset_block(rtc_data->io, true);
	stmp3xxx_clearl(BM_RTC_PERSISTENT0_ALARM_EN |
			BM_RTC_PERSISTENT0_ALARM_WAKE_EN |
			BM_RTC_PERSISTENT0_ALARM_WAKE,
			rtc_data->io + HW_RTC_PERSISTENT0);
	rtc_data->rtc = rtc_device_register(pdev->name, &pdev->dev,
				&stmp3xxx_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc_data->rtc)) {
		err = PTR_ERR(rtc_data->rtc);
		goto out_remap;
	}

	rtc_data->irq_count = 0;
	err = request_irq(rtc_data->irq_alarm, stmp3xxx_rtc_interrupt,
			IRQF_DISABLED, "RTC alarm", &pdev->dev);
	if (err) {
		dev_err(&pdev->dev, "Cannot claim IRQ%d\n",
			rtc_data->irq_alarm);
		goto out_irq_alarm;
	}
	err = request_irq(rtc_data->irq_1msec, stmp3xxx_rtc_interrupt,
			IRQF_DISABLED, "RTC tick", &pdev->dev);
	if (err) {
		dev_err(&pdev->dev, "Cannot claim IRQ%d\n",
			rtc_data->irq_1msec);
		goto out_irq1;
	}

	platform_set_drvdata(pdev, rtc_data);

	return 0;

out_irq1:
	free_irq(rtc_data->irq_alarm, &pdev->dev);
out_irq_alarm:
	stmp3xxx_clearl(BM_RTC_CTRL_ONEMSEC_IRQ_EN | BM_RTC_CTRL_ALARM_IRQ_EN,
			rtc_data->io + HW_RTC_CTRL);
	rtc_device_unregister(rtc_data->rtc);
out_remap:
	iounmap(rtc_data->io);
out_free:
	kfree(rtc_data);
	return err;
}