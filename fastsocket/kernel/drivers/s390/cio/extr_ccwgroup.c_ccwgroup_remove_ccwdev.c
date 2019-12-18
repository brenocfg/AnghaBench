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
struct ccwgroup_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  reg_mutex; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ccwgroup_remove_cdev_refs (struct ccwgroup_device*) ; 
 int /*<<< orphan*/  __ccwgroup_remove_symlinks (struct ccwgroup_device*) ; 
 int /*<<< orphan*/  ccw_device_set_offline (struct ccw_device*) ; 
 struct ccwgroup_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 scalar_t__ device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void ccwgroup_remove_ccwdev(struct ccw_device *cdev)
{
	struct ccwgroup_device *gdev;

	/* Ignore offlining errors, device is gone anyway. */
	ccw_device_set_offline(cdev);
	/* If one of its devices is gone, the whole group is done for. */
	spin_lock_irq(cdev->ccwlock);
	gdev = dev_get_drvdata(&cdev->dev);
	if (!gdev) {
		spin_unlock_irq(cdev->ccwlock);
		return;
	}
	/* Get ccwgroup device reference for local processing. */
	get_device(&gdev->dev);
	spin_unlock_irq(cdev->ccwlock);
	/* Unregister group device. */
	mutex_lock(&gdev->reg_mutex);
	if (device_is_registered(&gdev->dev)) {
		__ccwgroup_remove_symlinks(gdev);
		device_unregister(&gdev->dev);
		__ccwgroup_remove_cdev_refs(gdev);
	}
	mutex_unlock(&gdev->reg_mutex);
	/* Release ccwgroup device reference for local processing. */
	put_device(&gdev->dev);
}