#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct usb_gadget_driver {int /*<<< orphan*/  (* unbind ) (TYPE_2__*) ;TYPE_1__ driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct s3c2410_udc {struct usb_gadget_driver* driver; TYPE_2__ gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_NORMAL ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2410_udc_disable (struct s3c2410_udc*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 struct s3c2410_udc* the_controller ; 

int usb_gadget_unregister_driver(struct usb_gadget_driver *driver)
{
	struct s3c2410_udc *udc = the_controller;

	if (!udc)
		return -ENODEV;

	if (!driver || driver != udc->driver || !driver->unbind)
		return -EINVAL;

	dprintk(DEBUG_NORMAL,"usb_gadget_register_driver() '%s'\n",
		driver->driver.name);

	driver->unbind(&udc->gadget);

	device_del(&udc->gadget.dev);
	udc->driver = NULL;

	/* Disable udc */
	s3c2410_udc_disable(udc);

	return 0;
}