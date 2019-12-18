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
struct vme_driver {int (* remove ) (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct vme_bridge {int /*<<< orphan*/  num; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct vme_bridge* dev_to_bridge (struct device*) ; 
 struct vme_driver* dev_to_vme_driver (struct device*) ; 
 int stub1 (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vme_calc_slot (struct device*) ; 

__attribute__((used)) static int vme_bus_remove(struct device *dev)
{
	struct vme_bridge *bridge;
	struct vme_driver *driver;
	int retval = -ENODEV;

	driver = dev_to_vme_driver(dev);
	bridge = dev_to_bridge(dev);

	if(driver->remove != NULL) {
		retval = driver->remove(dev, bridge->num, vme_calc_slot(dev));
	}

	return retval;
}