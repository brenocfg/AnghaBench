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
struct rtc_device {int dummy; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_DISABLED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct rtc_device*) ; 
 struct rtc_device* platform_get_drvdata (struct platform_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct rtc_device*) ; 
 int /*<<< orphan*/  s3c_rtc_alarmirq ; 
 int /*<<< orphan*/  s3c_rtc_alarmno ; 
 int /*<<< orphan*/  s3c_rtc_tickirq ; 
 int /*<<< orphan*/  s3c_rtc_tickno ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int s3c_rtc_open(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtc_device *rtc_dev = platform_get_drvdata(pdev);
	int ret;

	ret = request_irq(s3c_rtc_alarmno, s3c_rtc_alarmirq,
			  IRQF_DISABLED,  "s3c2410-rtc alarm", rtc_dev);

	if (ret) {
		dev_err(dev, "IRQ%d error %d\n", s3c_rtc_alarmno, ret);
		return ret;
	}

	ret = request_irq(s3c_rtc_tickno, s3c_rtc_tickirq,
			  IRQF_DISABLED,  "s3c2410-rtc tick", rtc_dev);

	if (ret) {
		dev_err(dev, "IRQ%d error %d\n", s3c_rtc_tickno, ret);
		goto tick_err;
	}

	return ret;

 tick_err:
	free_irq(s3c_rtc_alarmno, rtc_dev);
	return ret;
}