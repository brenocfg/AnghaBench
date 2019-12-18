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
struct device {int /*<<< orphan*/  driver; } ;
struct ccwgroup_driver {int /*<<< orphan*/  (* remove ) (struct ccwgroup_device*) ;} ;
struct ccwgroup_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_online ; 
 int /*<<< orphan*/  dev_attr_ungroup ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ccwgroup_device*) ; 
 struct ccwgroup_device* to_ccwgroupdev (struct device*) ; 
 struct ccwgroup_driver* to_ccwgroupdrv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ccwgroup_remove (struct device *dev)
{
	struct ccwgroup_device *gdev;
	struct ccwgroup_driver *gdrv;

	device_remove_file(dev, &dev_attr_online);
	device_remove_file(dev, &dev_attr_ungroup);

	if (!dev->driver)
		return 0;

	gdev = to_ccwgroupdev(dev);
	gdrv = to_ccwgroupdrv(dev->driver);

	if (gdrv->remove)
		gdrv->remove(gdev);

	return 0;
}