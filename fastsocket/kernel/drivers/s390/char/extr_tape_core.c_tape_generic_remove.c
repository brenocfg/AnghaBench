#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tape_device {int tape_state; TYPE_1__* cdev; int /*<<< orphan*/  cdev_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct ccw_device {TYPE_2__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBF_LH (int,char*,int /*<<< orphan*/ ,struct ccw_device*) ; 
#define  TS_INIT 130 
#define  TS_NOT_OPER 129 
#define  TS_UNUSED 128 
 int /*<<< orphan*/  __tape_discard_requests (struct tape_device*) ; 
 struct tape_device* dev_get_drvdata (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ccwdev_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tape_attr_group ; 
 int /*<<< orphan*/  tape_cleanup_device (struct tape_device*) ; 
 int /*<<< orphan*/  tape_put_device (struct tape_device*) ; 
 int /*<<< orphan*/  tape_state_set (struct tape_device*,int const) ; 

void
tape_generic_remove(struct ccw_device *cdev)
{
	struct tape_device *	device;

	device = dev_get_drvdata(&cdev->dev);
	if (!device) {
		return;
	}
	DBF_LH(3, "(%08x): tape_generic_remove(%p)\n", device->cdev_id, cdev);

	spin_lock_irq(get_ccwdev_lock(device->cdev));
	switch (device->tape_state) {
		case TS_INIT:
			tape_state_set(device, TS_NOT_OPER);
		case TS_NOT_OPER:
			/*
			 * Nothing to do.
			 */
			spin_unlock_irq(get_ccwdev_lock(device->cdev));
			break;
		case TS_UNUSED:
			/*
			 * Need only to release the device.
			 */
			tape_state_set(device, TS_NOT_OPER);
			spin_unlock_irq(get_ccwdev_lock(device->cdev));
			tape_cleanup_device(device);
			break;
		default:
			/*
			 * There may be requests on the queue. We will not get
			 * an interrupt for a request that was running. So we
			 * just post them all as I/O errors.
			 */
			DBF_EVENT(3, "(%08x): Drive in use vanished!\n",
				device->cdev_id);
			pr_warning("%s: A tape unit was detached while in "
				   "use\n", dev_name(&device->cdev->dev));
			tape_state_set(device, TS_NOT_OPER);
			__tape_discard_requests(device);
			spin_unlock_irq(get_ccwdev_lock(device->cdev));
			tape_cleanup_device(device);
	}

	if (dev_get_drvdata(&cdev->dev)) {
		sysfs_remove_group(&cdev->dev.kobj, &tape_attr_group);
		dev_set_drvdata(&cdev->dev, tape_put_device(dev_get_drvdata(&cdev->dev)));
	}
}