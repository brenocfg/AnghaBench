#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * bus; } ;
struct usb_gadget_driver {scalar_t__ speed; int (* bind ) (TYPE_6__*) ;int /*<<< orphan*/  (* unbind ) (TYPE_6__*) ;TYPE_4__ driver; int /*<<< orphan*/  setup; } ;
struct TYPE_12__ {TYPE_4__* driver; } ;
struct TYPE_13__ {TYPE_5__ dev; } ;
struct net2280 {int softconnect; struct usb_gadget_driver* driver; TYPE_6__ gadget; TYPE_3__* pdev; TYPE_2__* usb; TYPE_1__* ep; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  stdrsp; int /*<<< orphan*/  usbctl; } ;
struct TYPE_8__ {scalar_t__ irqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (struct net2280*,char*,int /*<<< orphan*/ ,int,...) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  dev_attr_function ; 
 int /*<<< orphan*/  dev_attr_queues ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ep0_start (struct net2280*) ; 
 int /*<<< orphan*/  net2280_led_active (struct net2280*,int) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*) ; 
 struct net2280* the_controller ; 

int usb_gadget_register_driver (struct usb_gadget_driver *driver)
{
	struct net2280		*dev = the_controller;
	int			retval;
	unsigned		i;

	/* insist on high speed support from the driver, since
	 * (dev->usb->xcvrdiag & FORCE_FULL_SPEED_MODE)
	 * "must not be used in normal operation"
	 */
	if (!driver
			|| driver->speed != USB_SPEED_HIGH
			|| !driver->bind
			|| !driver->setup)
		return -EINVAL;
	if (!dev)
		return -ENODEV;
	if (dev->driver)
		return -EBUSY;

	for (i = 0; i < 7; i++)
		dev->ep [i].irqs = 0;

	/* hook up the driver ... */
	dev->softconnect = 1;
	driver->driver.bus = NULL;
	dev->driver = driver;
	dev->gadget.dev.driver = &driver->driver;
	retval = driver->bind (&dev->gadget);
	if (retval) {
		DEBUG (dev, "bind to driver %s --> %d\n",
				driver->driver.name, retval);
		dev->driver = NULL;
		dev->gadget.dev.driver = NULL;
		return retval;
	}

	retval = device_create_file (&dev->pdev->dev, &dev_attr_function);
	if (retval) goto err_unbind;
	retval = device_create_file (&dev->pdev->dev, &dev_attr_queues);
	if (retval) goto err_func;

	/* ... then enable host detection and ep0; and we're ready
	 * for set_configuration as well as eventual disconnect.
	 */
	net2280_led_active (dev, 1);
	ep0_start (dev);

	DEBUG (dev, "%s ready, usbctl %08x stdrsp %08x\n",
			driver->driver.name,
			readl (&dev->usb->usbctl),
			readl (&dev->usb->stdrsp));

	/* pci writes may still be posted */
	return 0;

err_func:
	device_remove_file (&dev->pdev->dev, &dev_attr_function);
err_unbind:
	driver->unbind (&dev->gadget);
	dev->gadget.dev.driver = NULL;
	dev->driver = NULL;
	return retval;
}