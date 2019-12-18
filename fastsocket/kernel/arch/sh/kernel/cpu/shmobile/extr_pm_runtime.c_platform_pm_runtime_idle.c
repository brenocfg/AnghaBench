#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int hwblk_id; } ;
struct platform_device {TYPE_1__ archdata; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int pm_runtime_suspend (struct device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

int platform_pm_runtime_idle(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	int hwblk = pdev->archdata.hwblk_id;
	int ret = 0;

	dev_dbg(dev, "platform_pm_runtime_idle() [%d]\n", hwblk);

	/* ignore off-chip platform devices */
	if (!hwblk)
		goto out;

	/* interrupt context not allowed, use pm_runtime_put()! */
	might_sleep();

	/* suspend synchronously to disable clocks immediately */
	ret = pm_runtime_suspend(dev);
out:
	dev_dbg(dev, "platform_pm_runtime_idle() [%d] done!\n", hwblk);
	return ret;
}