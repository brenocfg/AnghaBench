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
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * bus; } ;
struct usb_gadget_driver {scalar_t__ speed; int (* bind ) (TYPE_3__*) ;TYPE_2__ driver; int /*<<< orphan*/  setup; int /*<<< orphan*/  disconnect; } ;
struct TYPE_4__ {TYPE_2__* driver; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;
struct goku_udc {TYPE_3__ gadget; struct usb_gadget_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct goku_udc*,char*,int /*<<< orphan*/ ,...) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ USB_SPEED_FULL ; 
 int stub1 (TYPE_3__*) ; 
 struct goku_udc* the_controller ; 
 int /*<<< orphan*/  udc_enable (struct goku_udc*) ; 

int usb_gadget_register_driver(struct usb_gadget_driver *driver)
{
	struct goku_udc	*dev = the_controller;
	int			retval;

	if (!driver
			|| driver->speed < USB_SPEED_FULL
			|| !driver->bind
			|| !driver->disconnect
			|| !driver->setup)
		return -EINVAL;
	if (!dev)
		return -ENODEV;
	if (dev->driver)
		return -EBUSY;

	/* hook up the driver */
	driver->driver.bus = NULL;
	dev->driver = driver;
	dev->gadget.dev.driver = &driver->driver;
	retval = driver->bind(&dev->gadget);
	if (retval) {
		DBG(dev, "bind to driver %s --> error %d\n",
				driver->driver.name, retval);
		dev->driver = NULL;
		dev->gadget.dev.driver = NULL;
		return retval;
	}

	/* then enable host detection and ep0; and we're ready
	 * for set_configuration as well as eventual disconnect.
	 */
	udc_enable(dev);

	DBG(dev, "registered gadget driver '%s'\n", driver->driver.name);
	return 0;
}