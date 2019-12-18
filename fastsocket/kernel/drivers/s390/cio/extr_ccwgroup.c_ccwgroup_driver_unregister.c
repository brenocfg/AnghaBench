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
struct device {int dummy; } ;
struct ccwgroup_driver {int /*<<< orphan*/  driver; } ;
struct ccwgroup_device {int /*<<< orphan*/  reg_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ccwgroup_match_all ; 
 int /*<<< orphan*/  __ccwgroup_remove_cdev_refs (struct ccwgroup_device*) ; 
 int /*<<< orphan*/  __ccwgroup_remove_symlinks (struct ccwgroup_device*) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 struct device* driver_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  put_driver (int /*<<< orphan*/ *) ; 
 struct ccwgroup_device* to_ccwgroupdev (struct device*) ; 

void ccwgroup_driver_unregister(struct ccwgroup_driver *cdriver)
{
	struct device *dev;

	/* We don't want ccwgroup devices to live longer than their driver. */
	get_driver(&cdriver->driver);
	while ((dev = driver_find_device(&cdriver->driver, NULL, NULL,
					 __ccwgroup_match_all))) {
		struct ccwgroup_device *gdev = to_ccwgroupdev(dev);

		mutex_lock(&gdev->reg_mutex);
		__ccwgroup_remove_symlinks(gdev);
		device_unregister(dev);
		__ccwgroup_remove_cdev_refs(gdev);
		mutex_unlock(&gdev->reg_mutex);
		put_device(dev);
	}
	put_driver(&cdriver->driver);
	driver_unregister(&cdriver->driver);
}