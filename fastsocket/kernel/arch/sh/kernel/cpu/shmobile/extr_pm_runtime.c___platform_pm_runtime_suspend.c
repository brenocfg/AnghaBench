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
struct TYPE_3__ {int (* runtime_suspend ) (struct device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOSYS ; 
 int /*<<< orphan*/  HWBLK_CNT_IDLE ; 
 int /*<<< orphan*/  PDEV_ARCHDATA_FLAG_IDLE ; 
 int /*<<< orphan*/  PDEV_ARCHDATA_FLAG_SUSP ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  hwblk_cnt_dec (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwblk_disable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hwblk_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hwblk_info ; 
 int /*<<< orphan*/  platform_pm_runtime_not_idle (struct platform_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __platform_pm_runtime_suspend(struct platform_device *pdev)
{
	struct device *d = &pdev->dev;
	struct pdev_archdata *ad = &pdev->archdata;
	int hwblk = ad->hwblk_id;
	int ret = -ENOSYS;

	dev_dbg(d, "__platform_pm_runtime_suspend() [%d]\n", hwblk);

	if (d->driver && d->driver->pm && d->driver->pm->runtime_suspend) {
		BUG_ON(!test_bit(PDEV_ARCHDATA_FLAG_IDLE, &ad->flags));

		hwblk_enable(hwblk_info, hwblk);
		ret = d->driver->pm->runtime_suspend(d);
		hwblk_disable(hwblk_info, hwblk);

		if (!ret) {
			set_bit(PDEV_ARCHDATA_FLAG_SUSP, &ad->flags);
			platform_pm_runtime_not_idle(pdev);
			hwblk_cnt_dec(hwblk_info, hwblk, HWBLK_CNT_IDLE);
		}
	}

	dev_dbg(d, "__platform_pm_runtime_suspend() [%d] - returns %d\n",
		hwblk, ret);

	return ret;
}