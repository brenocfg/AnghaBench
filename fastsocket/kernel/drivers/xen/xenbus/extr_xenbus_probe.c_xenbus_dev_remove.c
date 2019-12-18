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
struct xenbus_driver {int /*<<< orphan*/  (* remove ) (struct xenbus_device*) ;} ;
struct xenbus_device {int /*<<< orphan*/  nodename; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XenbusStateClosed ; 
 int /*<<< orphan*/  free_otherend_details (struct xenbus_device*) ; 
 int /*<<< orphan*/  free_otherend_watch (struct xenbus_device*) ; 
 int /*<<< orphan*/  stub1 (struct xenbus_device*) ; 
 struct xenbus_device* to_xenbus_device (struct device*) ; 
 struct xenbus_driver* to_xenbus_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_switch_state (struct xenbus_device*,int /*<<< orphan*/ ) ; 

int xenbus_dev_remove(struct device *_dev)
{
	struct xenbus_device *dev = to_xenbus_device(_dev);
	struct xenbus_driver *drv = to_xenbus_driver(_dev->driver);

	DPRINTK("%s", dev->nodename);

	free_otherend_watch(dev);
	free_otherend_details(dev);

	if (drv->remove)
		drv->remove(dev);

	xenbus_switch_state(dev, XenbusStateClosed);
	return 0;
}