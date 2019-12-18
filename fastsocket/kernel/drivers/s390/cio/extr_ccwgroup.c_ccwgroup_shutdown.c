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
struct ccwgroup_driver {int /*<<< orphan*/  (* shutdown ) (struct ccwgroup_device*) ;} ;
struct ccwgroup_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ccwgroup_device*) ; 
 struct ccwgroup_device* to_ccwgroupdev (struct device*) ; 
 struct ccwgroup_driver* to_ccwgroupdrv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccwgroup_shutdown(struct device *dev)
{
	struct ccwgroup_device *gdev;
	struct ccwgroup_driver *gdrv;

	if (!dev->driver)
		return;

	gdev = to_ccwgroupdev(dev);
	gdrv = to_ccwgroupdrv(dev->driver);

	if (gdrv->shutdown)
		gdrv->shutdown(gdev);
}