#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct usb_gadget_driver {scalar_t__ speed; int (* bind ) (TYPE_2__*) ;int /*<<< orphan*/  (* unbind ) (TYPE_2__*) ;TYPE_1__ driver; int /*<<< orphan*/  setup; int /*<<< orphan*/  disconnect; } ;
struct TYPE_9__ {TYPE_1__* driver; } ;
struct TYPE_8__ {TYPE_5__ dev; } ;
struct pxa25x_udc {int pullup; TYPE_2__ gadget; scalar_t__ transceiver; struct usb_gadget_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMSG (char*,...) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ USB_SPEED_FULL ; 
 int device_add (TYPE_5__*) ; 
 int /*<<< orphan*/  device_del (TYPE_5__*) ; 
 int /*<<< orphan*/  dump_state (struct pxa25x_udc*) ; 
 int otg_set_peripheral (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  pullup (struct pxa25x_udc*) ; 
 int stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 struct pxa25x_udc* the_controller ; 

int usb_gadget_register_driver(struct usb_gadget_driver *driver)
{
	struct pxa25x_udc	*dev = the_controller;
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

	/* first hook up the driver ... */
	dev->driver = driver;
	dev->gadget.dev.driver = &driver->driver;
	dev->pullup = 1;

	retval = device_add (&dev->gadget.dev);
	if (retval) {
fail:
		dev->driver = NULL;
		dev->gadget.dev.driver = NULL;
		return retval;
	}
	retval = driver->bind(&dev->gadget);
	if (retval) {
		DMSG("bind to driver %s --> error %d\n",
				driver->driver.name, retval);
		device_del (&dev->gadget.dev);
		goto fail;
	}

	/* ... then enable host detection and ep0; and we're ready
	 * for set_configuration as well as eventual disconnect.
	 */
	DMSG("registered gadget driver '%s'\n", driver->driver.name);

	/* connect to bus through transceiver */
	if (dev->transceiver) {
		retval = otg_set_peripheral(dev->transceiver, &dev->gadget);
		if (retval) {
			DMSG("can't bind to transceiver\n");
			if (driver->unbind)
				driver->unbind(&dev->gadget);
			goto bind_fail;
		}
	}

	pullup(dev);
	dump_state(dev);
	return 0;
bind_fail:
	return retval;
}