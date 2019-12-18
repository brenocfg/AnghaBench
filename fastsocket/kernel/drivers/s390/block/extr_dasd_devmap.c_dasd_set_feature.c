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
struct dasd_devmap {int features; TYPE_1__* device; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dasd_devmap*) ; 
 int PTR_ERR (struct dasd_devmap*) ; 
 int /*<<< orphan*/  dasd_devmap_lock ; 
 struct dasd_devmap* dasd_find_busid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int
dasd_set_feature(struct ccw_device *cdev, int feature, int flag)
{
	struct dasd_devmap *devmap;

	devmap = dasd_find_busid(dev_name(&cdev->dev));
	if (IS_ERR(devmap))
		return PTR_ERR(devmap);

	spin_lock(&dasd_devmap_lock);
	if (flag)
		devmap->features |= feature;
	else
		devmap->features &= ~feature;
	if (devmap->device)
		devmap->device->features = devmap->features;
	spin_unlock(&dasd_devmap_lock);
	return 0;
}