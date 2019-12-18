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
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct usb_gadget_driver {TYPE_1__ driver; int /*<<< orphan*/  (* unbind ) (TYPE_2__*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/ * driver; } ;
struct TYPE_5__ {TYPE_3__ dev; } ;
struct pxa25x_udc {TYPE_2__ gadget; struct usb_gadget_driver* driver; scalar_t__ transceiver; scalar_t__ pullup; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMSG (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  device_del (TYPE_3__*) ; 
 int /*<<< orphan*/  dump_state (struct pxa25x_udc*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  otg_set_peripheral (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pullup (struct pxa25x_udc*) ; 
 int /*<<< orphan*/  stop_activity (struct pxa25x_udc*,struct usb_gadget_driver*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 struct pxa25x_udc* the_controller ; 

int usb_gadget_unregister_driver(struct usb_gadget_driver *driver)
{
	struct pxa25x_udc	*dev = the_controller;

	if (!dev)
		return -ENODEV;
	if (!driver || driver != dev->driver || !driver->unbind)
		return -EINVAL;

	local_irq_disable();
	dev->pullup = 0;
	pullup(dev);
	stop_activity(dev, driver);
	local_irq_enable();

	if (dev->transceiver)
		(void) otg_set_peripheral(dev->transceiver, NULL);

	driver->unbind(&dev->gadget);
	dev->gadget.dev.driver = NULL;
	dev->driver = NULL;

	device_del (&dev->gadget.dev);

	DMSG("unregistered gadget driver '%s'\n", driver->driver.name);
	dump_state(dev);
	return 0;
}