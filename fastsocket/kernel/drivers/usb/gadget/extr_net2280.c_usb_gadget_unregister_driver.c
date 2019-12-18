#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct usb_gadget_driver {TYPE_3__ driver; int /*<<< orphan*/  (* unbind ) (TYPE_4__*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/ * driver; } ;
struct TYPE_9__ {TYPE_1__ dev; } ;
struct net2280 {TYPE_2__* pdev; struct usb_gadget_driver* driver; TYPE_4__ gadget; int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (struct net2280*,char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_attr_function ; 
 int /*<<< orphan*/  dev_attr_queues ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net2280_led_active (struct net2280*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net2280_pullup (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stop_activity (struct net2280*,struct usb_gadget_driver*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 struct net2280* the_controller ; 

int usb_gadget_unregister_driver (struct usb_gadget_driver *driver)
{
	struct net2280	*dev = the_controller;
	unsigned long	flags;

	if (!dev)
		return -ENODEV;
	if (!driver || driver != dev->driver || !driver->unbind)
		return -EINVAL;

	spin_lock_irqsave (&dev->lock, flags);
	stop_activity (dev, driver);
	spin_unlock_irqrestore (&dev->lock, flags);

	net2280_pullup (&dev->gadget, 0);

	driver->unbind (&dev->gadget);
	dev->gadget.dev.driver = NULL;
	dev->driver = NULL;

	net2280_led_active (dev, 0);
	device_remove_file (&dev->pdev->dev, &dev_attr_function);
	device_remove_file (&dev->pdev->dev, &dev_attr_queues);

	DEBUG (dev, "unregistered driver '%s'\n", driver->driver.name);
	return 0;
}