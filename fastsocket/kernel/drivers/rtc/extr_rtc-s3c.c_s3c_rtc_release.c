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
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct rtc_device*) ; 
 struct rtc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  s3c_rtc_alarmno ; 
 int /*<<< orphan*/  s3c_rtc_setpie (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_rtc_tickno ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static void s3c_rtc_release(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtc_device *rtc_dev = platform_get_drvdata(pdev);

	/* do not clear AIE here, it may be needed for wake */

	s3c_rtc_setpie(dev, 0);
	free_irq(s3c_rtc_alarmno, rtc_dev);
	free_irq(s3c_rtc_tickno, rtc_dev);
}