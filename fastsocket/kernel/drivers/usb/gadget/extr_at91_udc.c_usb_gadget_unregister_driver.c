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
struct at91_udc {struct usb_gadget_driver* driver; TYPE_2__ gadget; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_UDP_IDR ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  at91_udp_write (struct at91_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct at91_udc controller ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  pullup (struct at91_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

int usb_gadget_unregister_driver (struct usb_gadget_driver *driver)
{
	struct at91_udc *udc = &controller;

	if (!driver || driver != udc->driver || !driver->unbind)
		return -EINVAL;

	local_irq_disable();
	udc->enabled = 0;
	at91_udp_write(udc, AT91_UDP_IDR, ~0);
	pullup(udc, 0);
	local_irq_enable();

	driver->unbind(&udc->gadget);
	udc->gadget.dev.driver = NULL;
	dev_set_drvdata(&udc->gadget.dev, NULL);
	udc->driver = NULL;

	DBG("unbound from %s\n", driver->driver.name);
	return 0;
}