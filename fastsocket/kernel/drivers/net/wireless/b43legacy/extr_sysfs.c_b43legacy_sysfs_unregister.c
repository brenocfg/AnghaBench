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
struct device {int dummy; } ;
struct b43legacy_wldev {TYPE_1__* dev; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_interference ; 
 int /*<<< orphan*/  dev_attr_shortpreamble ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 

void b43legacy_sysfs_unregister(struct b43legacy_wldev *wldev)
{
	struct device *dev = wldev->dev->dev;

	device_remove_file(dev, &dev_attr_shortpreamble);
	device_remove_file(dev, &dev_attr_interference);
}