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
struct dasd_devmap {struct dasd_device* device; } ;
struct dasd_device {struct ccw_device* cdev; int /*<<< orphan*/  ref_count; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct dasd_devmap*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dasd_delete_wq ; 
 int /*<<< orphan*/  dasd_devmap_lock ; 
 struct dasd_devmap* dasd_find_busid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_free_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ccwdev_lock (struct ccw_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void
dasd_delete_device(struct dasd_device *device)
{
	struct ccw_device *cdev;
	struct dasd_devmap *devmap;
	unsigned long flags;

	/* First remove device pointer from devmap. */
	devmap = dasd_find_busid(dev_name(&device->cdev->dev));
	BUG_ON(IS_ERR(devmap));
	spin_lock(&dasd_devmap_lock);
	if (devmap->device != device) {
		spin_unlock(&dasd_devmap_lock);
		dasd_put_device(device);
		return;
	}
	devmap->device = NULL;
	spin_unlock(&dasd_devmap_lock);

	/* Disconnect dasd_device structure from ccw_device structure. */
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	dev_set_drvdata(&device->cdev->dev, NULL);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);

	/*
	 * Drop ref_count by 3, one for the devmap reference, one for
	 * the cdev reference and one for the passed reference.
	 */
	atomic_sub(3, &device->ref_count);

	/* Wait for reference counter to drop to zero. */
	wait_event(dasd_delete_wq, atomic_read(&device->ref_count) == 0);

	/* Disconnect dasd_device structure from ccw_device structure. */
	cdev = device->cdev;
	device->cdev = NULL;

	/* Put ccw_device structure. */
	put_device(&cdev->dev);

	/* Now the device structure can be freed. */
	dasd_free_device(device);
}