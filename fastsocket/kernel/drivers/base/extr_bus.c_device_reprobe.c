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
struct device {TYPE_1__* parent; scalar_t__ driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 int bus_rescan_devices_helper (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_release_driver (struct device*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int device_reprobe(struct device *dev)
{
	if (dev->driver) {
		if (dev->parent)        /* Needed for USB */
			down(&dev->parent->sem);
		device_release_driver(dev);
		if (dev->parent)
			up(&dev->parent->sem);
	}
	return bus_rescan_devices_helper(dev, NULL);
}