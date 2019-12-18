#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  parent; } ;
struct subchannel {int /*<<< orphan*/  lock; TYPE_4__ dev; } ;
struct ccw_device {TYPE_3__* private; TYPE_4__ dev; int /*<<< orphan*/  drv; } ;
struct TYPE_9__ {int recog_done; } ;
struct TYPE_8__ {int ssid; int devno; } ;
struct TYPE_10__ {int /*<<< orphan*/  wait_q; TYPE_2__ flags; TYPE_1__ dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccw_device_init_count ; 
 int /*<<< orphan*/  ccw_device_init_wq ; 
 int ccw_device_register (struct ccw_device*) ; 
 int /*<<< orphan*/  css_update_ssd_info (struct subchannel*) ; 
 int /*<<< orphan*/  dev_set_uevent_suppress (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_registered (TYPE_4__*) ; 
 int device_reprobe (TYPE_4__*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_4__*) ; 
 int /*<<< orphan*/  sch_set_cdev (struct subchannel*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void io_subchannel_register(struct ccw_device *cdev)
{
	struct subchannel *sch;
	int ret, adjust_init_count = 1;
	unsigned long flags;

	sch = to_subchannel(cdev->dev.parent);
	/*
	 * Check if subchannel is still registered. It may have become
	 * unregistered if a machine check hit us after finishing
	 * device recognition but before the register work could be
	 * queued.
	 */
	if (!device_is_registered(&sch->dev))
		goto out_err;
	css_update_ssd_info(sch);
	/*
	 * io_subchannel_register() will also be called after device
	 * recognition has been done for a boxed device (which will already
	 * be registered). We need to reprobe since we may now have sense id
	 * information.
	 */
	if (device_is_registered(&cdev->dev)) {
		if (!cdev->drv) {
			ret = device_reprobe(&cdev->dev);
			if (ret)
				/* We can't do much here. */
				CIO_MSG_EVENT(0, "device_reprobe() returned"
					      " %d for 0.%x.%04x\n", ret,
					      cdev->private->dev_id.ssid,
					      cdev->private->dev_id.devno);
		}
		adjust_init_count = 0;
		goto out;
	}
	/*
	 * Now we know this subchannel will stay, we can throw
	 * our delayed uevent.
	 */
	dev_set_uevent_suppress(&sch->dev, 0);
	kobject_uevent(&sch->dev.kobj, KOBJ_ADD);
	/* make it known to the system */
	ret = ccw_device_register(cdev);
	if (ret) {
		CIO_MSG_EVENT(0, "Could not register ccw dev 0.%x.%04x: %d\n",
			      cdev->private->dev_id.ssid,
			      cdev->private->dev_id.devno, ret);
		spin_lock_irqsave(sch->lock, flags);
		sch_set_cdev(sch, NULL);
		spin_unlock_irqrestore(sch->lock, flags);
		/* Release initial device reference. */
		put_device(&cdev->dev);
		goto out_err;
	}
out:
	cdev->private->flags.recog_done = 1;
	wake_up(&cdev->private->wait_q);
out_err:
	if (adjust_init_count && atomic_dec_and_test(&ccw_device_init_count))
		wake_up(&ccw_device_init_wq);
}