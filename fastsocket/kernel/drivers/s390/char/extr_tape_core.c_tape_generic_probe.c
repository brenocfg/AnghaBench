#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tape_device {int /*<<< orphan*/  cdev_id; struct ccw_device* cdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct ccw_device {int /*<<< orphan*/  handler; TYPE_1__ dev; } ;
struct ccw_dev_id {int dummy; } ;

/* Variables and functions */
 int CCWDEV_DO_MULTIPATH ; 
 int CCWDEV_DO_PATHGROUP ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct tape_device*) ; 
 int /*<<< orphan*/  __tape_do_irq ; 
 int /*<<< orphan*/  ccw_device_get_id (struct ccw_device*,struct ccw_dev_id*) ; 
 int /*<<< orphan*/  ccw_device_set_options (struct ccw_device*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct tape_device*) ; 
 int /*<<< orphan*/  devid_to_int (struct ccw_dev_id*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct tape_device* tape_alloc_device () ; 
 int /*<<< orphan*/  tape_attr_group ; 
 int /*<<< orphan*/  tape_put_device (struct tape_device*) ; 

int
tape_generic_probe(struct ccw_device *cdev)
{
	struct tape_device *device;
	int ret;
	struct ccw_dev_id dev_id;

	device = tape_alloc_device();
	if (IS_ERR(device))
		return -ENODEV;
	ccw_device_set_options(cdev, CCWDEV_DO_PATHGROUP |
				     CCWDEV_DO_MULTIPATH);
	ret = sysfs_create_group(&cdev->dev.kobj, &tape_attr_group);
	if (ret) {
		tape_put_device(device);
		return ret;
	}
	dev_set_drvdata(&cdev->dev, device);
	cdev->handler = __tape_do_irq;
	device->cdev = cdev;
	ccw_device_get_id(cdev, &dev_id);
	device->cdev_id = devid_to_int(&dev_id);
	return ret;
}