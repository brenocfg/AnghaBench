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
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct subchannel {TYPE_1__ dev; int /*<<< orphan*/  private; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; TYPE_2__* private; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_STATE_NOT_OPER ; 
 int /*<<< orphan*/  ccw_device_unregister (struct ccw_device*) ; 
 int /*<<< orphan*/  io_subchannel_attr_group ; 
 int /*<<< orphan*/  io_subchannel_quiesce (struct subchannel*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct ccw_device* sch_get_cdev (struct subchannel*) ; 
 int /*<<< orphan*/  sch_set_cdev (struct subchannel*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
io_subchannel_remove (struct subchannel *sch)
{
	struct ccw_device *cdev;
	unsigned long flags;

	cdev = sch_get_cdev(sch);
	if (!cdev)
		goto out_free;
	io_subchannel_quiesce(sch);
	/* Set ccw device to not operational and drop reference. */
	spin_lock_irqsave(cdev->ccwlock, flags);
	sch_set_cdev(sch, NULL);
	cdev->private->state = DEV_STATE_NOT_OPER;
	spin_unlock_irqrestore(cdev->ccwlock, flags);
	ccw_device_unregister(cdev);
out_free:
	kfree(sch->private);
	sysfs_remove_group(&sch->dev.kobj, &io_subchannel_attr_group);
	return 0;
}