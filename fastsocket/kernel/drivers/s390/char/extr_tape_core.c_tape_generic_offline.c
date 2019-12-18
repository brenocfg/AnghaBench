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
struct tape_device {int tape_state; int /*<<< orphan*/  cdev_id; int /*<<< orphan*/  cdev; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBF_LH (int,char*,int /*<<< orphan*/ ,...) ; 
 int EBUSY ; 
 int ENODEV ; 
#define  TS_INIT 130 
#define  TS_NOT_OPER 129 
#define  TS_UNUSED 128 
 struct tape_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tape_cleanup_device (struct tape_device*) ; 
 int /*<<< orphan*/  tape_state_set (struct tape_device*,int const) ; 

int
tape_generic_offline(struct ccw_device *cdev)
{
	struct tape_device *device;

	device = dev_get_drvdata(&cdev->dev);
	if (!device) {
		return -ENODEV;
	}

	DBF_LH(3, "(%08x): tape_generic_offline(%p)\n",
		device->cdev_id, device);

	spin_lock_irq(get_ccwdev_lock(device->cdev));
	switch (device->tape_state) {
		case TS_INIT:
		case TS_NOT_OPER:
			spin_unlock_irq(get_ccwdev_lock(device->cdev));
			break;
		case TS_UNUSED:
			tape_state_set(device, TS_INIT);
			spin_unlock_irq(get_ccwdev_lock(device->cdev));
			tape_cleanup_device(device);
			break;
		default:
			DBF_EVENT(3, "(%08x): Set offline failed "
				"- drive in use.\n",
				device->cdev_id);
			spin_unlock_irq(get_ccwdev_lock(device->cdev));
			return -EBUSY;
	}

	DBF_LH(3, "(%08x): Drive set offline.\n", device->cdev_id);
	return 0;
}