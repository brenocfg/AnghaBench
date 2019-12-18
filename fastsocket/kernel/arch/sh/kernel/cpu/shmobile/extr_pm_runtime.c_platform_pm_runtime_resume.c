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
struct pdev_archdata {int hwblk_id; int /*<<< orphan*/  mutex; int /*<<< orphan*/  flags; } ;
struct platform_device {struct pdev_archdata archdata; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWBLK_CNT_IDLE ; 
 int /*<<< orphan*/  PDEV_ARCHDATA_FLAG_INIT ; 
 int /*<<< orphan*/  PDEV_ARCHDATA_FLAG_SUSP ; 
 int __platform_pm_runtime_resume (struct platform_device*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  hwblk_cnt_dec (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwblk_info ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_pm_runtime_not_idle (struct platform_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (struct device*) ; 

int platform_pm_runtime_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct pdev_archdata *ad = &pdev->archdata;
	int hwblk = ad->hwblk_id;
	int ret = 0;

	dev_dbg(dev, "platform_pm_runtime_resume() [%d]\n", hwblk);

	/* ignore off-chip platform devices */
	if (!hwblk)
		goto out;

	/* interrupt context not allowed */
	might_sleep();

	/* serialize */
	mutex_lock(&ad->mutex);

	/* make sure device is removed from idle list */
	platform_pm_runtime_not_idle(pdev);

	/* decrease idle count */
	if (!test_bit(PDEV_ARCHDATA_FLAG_INIT, &pdev->archdata.flags) &&
	    !test_bit(PDEV_ARCHDATA_FLAG_SUSP, &pdev->archdata.flags))
		hwblk_cnt_dec(hwblk_info, hwblk, HWBLK_CNT_IDLE);

	/* resume the device if needed */
	ret = __platform_pm_runtime_resume(pdev);

	/* the driver has been initialized now, so clear the init flag */
	clear_bit(PDEV_ARCHDATA_FLAG_INIT, &pdev->archdata.flags);

	/* at this point the platform device may be:
	 * resumed: ret = 0, flags = 0, clock started
	 * failed: ret < 0, FLAG_SUSP set, clock stopped
	 */
	mutex_unlock(&ad->mutex);
out:
	dev_dbg(dev, "platform_pm_runtime_resume() [%d] returns %d\n",
		hwblk, ret);

	return ret;
}