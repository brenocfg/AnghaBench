#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct subchannel {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_3__* private; TYPE_2__* drv; int /*<<< orphan*/  online; TYPE_1__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/ * cmb; } ;
struct TYPE_5__ {int (* freeze ) (struct ccw_device*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int ccw_set_cmf (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int cio_disable_subchannel (struct subchannel*) ; 
 int /*<<< orphan*/  dev_fsm_final_state (struct ccw_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int stub1 (struct ccw_device*) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccw_device_pm_freeze(struct device *dev)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	int ret, cm_enabled;

	/* Fail suspend while device is in transistional state. */
	if (!dev_fsm_final_state(cdev))
		return -EAGAIN;
	if (!cdev->online)
		return 0;
	if (cdev->drv && cdev->drv->freeze) {
		ret = cdev->drv->freeze(cdev);
		if (ret)
			return ret;
	}

	spin_lock_irq(sch->lock);
	cm_enabled = cdev->private->cmb != NULL;
	spin_unlock_irq(sch->lock);
	if (cm_enabled) {
		/* Don't have the css write on memory. */
		ret = ccw_set_cmf(cdev, 0);
		if (ret)
			return ret;
	}
	/* From here on, disallow device driver I/O. */
	spin_lock_irq(sch->lock);
	ret = cio_disable_subchannel(sch);
	spin_unlock_irq(sch->lock);

	return ret;
}