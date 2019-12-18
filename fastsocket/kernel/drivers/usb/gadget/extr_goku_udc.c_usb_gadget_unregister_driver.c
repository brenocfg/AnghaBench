#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct usb_gadget_driver {TYPE_2__ driver; int /*<<< orphan*/  (* unbind ) (TYPE_3__*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/ * driver; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;
struct goku_udc {TYPE_3__ gadget; int /*<<< orphan*/  lock; struct usb_gadget_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct goku_udc*,char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stop_activity (struct goku_udc*,struct usb_gadget_driver*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 struct goku_udc* the_controller ; 

int usb_gadget_unregister_driver(struct usb_gadget_driver *driver)
{
	struct goku_udc	*dev = the_controller;
	unsigned long	flags;

	if (!dev)
		return -ENODEV;
	if (!driver || driver != dev->driver || !driver->unbind)
		return -EINVAL;

	spin_lock_irqsave(&dev->lock, flags);
	dev->driver = NULL;
	stop_activity(dev, driver);
	spin_unlock_irqrestore(&dev->lock, flags);

	driver->unbind(&dev->gadget);
	dev->gadget.dev.driver = NULL;

	DBG(dev, "unregistered driver '%s'\n", driver->driver.name);
	return 0;
}