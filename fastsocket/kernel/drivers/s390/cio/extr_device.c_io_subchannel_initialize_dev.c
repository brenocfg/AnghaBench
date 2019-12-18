#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct subchannel {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  groups; int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct ccw_device {TYPE_2__* private; TYPE_3__ dev; } ;
struct TYPE_5__ {int initialized; } ;
struct TYPE_6__ {TYPE_1__ flags; int /*<<< orphan*/  todo_work; int /*<<< orphan*/  onoff; struct ccw_device* cdev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_release ; 
 int /*<<< orphan*/  ccw_device_todo ; 
 int /*<<< orphan*/  ccwdev_attr_groups ; 
 int /*<<< orphan*/  device_initialize (TYPE_3__*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_3__*) ; 

__attribute__((used)) static int io_subchannel_initialize_dev(struct subchannel *sch,
					struct ccw_device *cdev)
{
	cdev->private->cdev = cdev;
	atomic_set(&cdev->private->onoff, 0);
	cdev->dev.parent = &sch->dev;
	cdev->dev.release = ccw_device_release;
	INIT_WORK(&cdev->private->todo_work, ccw_device_todo);
	cdev->dev.groups = ccwdev_attr_groups;
	/* Do first half of device_register. */
	device_initialize(&cdev->dev);
	if (!get_device(&sch->dev)) {
		/* Release reference from device_initialize(). */
		put_device(&cdev->dev);
		return -ENODEV;
	}
	cdev->private->flags.initialized = 1;
	return 0;
}