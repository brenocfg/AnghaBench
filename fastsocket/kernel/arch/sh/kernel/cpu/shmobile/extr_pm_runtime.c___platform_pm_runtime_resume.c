#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pdev_archdata {int hwblk_id; int /*<<< orphan*/  flags; } ;
struct device {TYPE_2__* driver; } ;
struct platform_device {struct pdev_archdata archdata; struct device dev; } ;
struct TYPE_4__ {TYPE_1__* pm; } ;
struct TYPE_3__ {int (* runtime_resume ) (struct device*) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  PDEV_ARCHDATA_FLAG_SUSP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  hwblk_disable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hwblk_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hwblk_info ; 
 int stub1 (struct device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __platform_pm_runtime_resume(struct platform_device *pdev)
{
	struct device *d = &pdev->dev;
	struct pdev_archdata *ad = &pdev->archdata;
	int hwblk = ad->hwblk_id;
	int ret = -ENOSYS;

	dev_dbg(d, "__platform_pm_runtime_resume() [%d]\n", hwblk);

	if (d->driver && d->driver->pm && d->driver->pm->runtime_resume) {
		hwblk_enable(hwblk_info, hwblk);
		ret = 0;

		if (test_bit(PDEV_ARCHDATA_FLAG_SUSP, &ad->flags)) {
			ret = d->driver->pm->runtime_resume(d);
			if (!ret)
				clear_bit(PDEV_ARCHDATA_FLAG_SUSP, &ad->flags);
			else
				hwblk_disable(hwblk_info, hwblk);
		}
	}

	dev_dbg(d, "__platform_pm_runtime_resume() [%d] - returns %d\n",
		hwblk, ret);

	return ret;
}