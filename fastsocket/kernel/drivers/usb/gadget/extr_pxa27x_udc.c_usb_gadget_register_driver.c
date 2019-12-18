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
struct pxa_udc {TYPE_2__ gadget; struct usb_gadget_driver* driver; int /*<<< orphan*/  dev; scalar_t__ transceiver; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ USB_SPEED_FULL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int device_add (TYPE_5__*) ; 
 int /*<<< orphan*/  device_del (TYPE_5__*) ; 
 int /*<<< orphan*/  dplus_pullup (struct pxa_udc*,int) ; 
 int otg_set_peripheral (scalar_t__,TYPE_2__*) ; 
 scalar_t__ should_enable_udc (struct pxa_udc*) ; 
 int stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 struct pxa_udc* the_controller ; 
 int /*<<< orphan*/  udc_enable (struct pxa_udc*) ; 

int usb_gadget_register_driver(struct usb_gadget_driver *driver)
{
	struct pxa_udc *udc = the_controller;
	int retval;

	if (!driver || driver->speed < USB_SPEED_FULL || !driver->bind
			|| !driver->disconnect || !driver->setup)
		return -EINVAL;
	if (!udc)
		return -ENODEV;
	if (udc->driver)
		return -EBUSY;

	/* first hook up the driver ... */
	udc->driver = driver;
	udc->gadget.dev.driver = &driver->driver;
	dplus_pullup(udc, 1);

	retval = device_add(&udc->gadget.dev);
	if (retval) {
		dev_err(udc->dev, "device_add error %d\n", retval);
		goto add_fail;
	}
	retval = driver->bind(&udc->gadget);
	if (retval) {
		dev_err(udc->dev, "bind to driver %s --> error %d\n",
			driver->driver.name, retval);
		goto bind_fail;
	}
	dev_dbg(udc->dev, "registered gadget driver '%s'\n",
		driver->driver.name);

	if (udc->transceiver) {
		retval = otg_set_peripheral(udc->transceiver, &udc->gadget);
		if (retval) {
			dev_err(udc->dev, "can't bind to transceiver\n");
			goto transceiver_fail;
		}
	}

	if (should_enable_udc(udc))
		udc_enable(udc);
	return 0;

transceiver_fail:
	if (driver->unbind)
		driver->unbind(&udc->gadget);
bind_fail:
	device_del(&udc->gadget.dev);
add_fail:
	udc->driver = NULL;
	udc->gadget.dev.driver = NULL;
	return retval;
}