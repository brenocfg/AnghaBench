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
struct pdev_archdata {int hwblk_id; int /*<<< orphan*/  mutex; int /*<<< orphan*/  flags; int /*<<< orphan*/  entry; } ;
struct platform_device {struct pdev_archdata archdata; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HWBLK_CNT_IDLE ; 
 int /*<<< orphan*/  PDEV_ARCHDATA_FLAG_IDLE ; 
 int /*<<< orphan*/  PDEV_ARCHDATA_FLAG_INIT ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  hwblk_cnt_inc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwblk_disable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hwblk_idle_list ; 
 int /*<<< orphan*/  hwblk_info ; 
 int /*<<< orphan*/  hwblk_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (struct device*) ; 

int platform_pm_runtime_suspend(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct pdev_archdata *ad = &pdev->archdata;
	unsigned long flags;
	int hwblk = ad->hwblk_id;
	int ret = 0;

	dev_dbg(dev, "platform_pm_runtime_suspend() [%d]\n", hwblk);

	/* ignore off-chip platform devices */
	if (!hwblk)
		goto out;

	/* interrupt context not allowed */
	might_sleep();

	/* catch misconfigured drivers not starting with resume */
	if (test_bit(PDEV_ARCHDATA_FLAG_INIT, &pdev->archdata.flags)) {
		ret = -EINVAL;
		goto out;
	}

	/* serialize */
	mutex_lock(&ad->mutex);

	/* disable clock */
	hwblk_disable(hwblk_info, hwblk);

	/* put device on idle list */
	spin_lock_irqsave(&hwblk_lock, flags);
	list_add_tail(&pdev->archdata.entry, &hwblk_idle_list);
	__set_bit(PDEV_ARCHDATA_FLAG_IDLE, &pdev->archdata.flags);
	spin_unlock_irqrestore(&hwblk_lock, flags);

	/* increase idle count */
	hwblk_cnt_inc(hwblk_info, hwblk, HWBLK_CNT_IDLE);

	/* at this point the platform device is:
	 * idle: ret = 0, FLAG_IDLE set, clock stopped
	 */
	mutex_unlock(&ad->mutex);

out:
	dev_dbg(dev, "platform_pm_runtime_suspend() [%d] returns %d\n",
		hwblk, ret);

	return ret;
}