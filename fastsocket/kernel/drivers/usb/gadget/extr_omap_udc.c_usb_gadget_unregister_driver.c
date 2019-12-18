#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct usb_gadget_driver {TYPE_2__ driver; int /*<<< orphan*/  (* unbind ) (TYPE_5__*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/ * driver; } ;
struct TYPE_11__ {TYPE_1__ dev; } ;
struct TYPE_10__ {int /*<<< orphan*/ * dc_clk; struct usb_gadget_driver* driver; TYPE_5__ gadget; int /*<<< orphan*/  lock; scalar_t__ transceiver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ machine_without_vbus_sense () ; 
 int /*<<< orphan*/  omap_udc_enable_clock (int) ; 
 int /*<<< orphan*/  omap_vbus_session (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_set_peripheral (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pullup_disable (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 TYPE_3__* udc ; 
 int /*<<< orphan*/  udc_quiesce (TYPE_3__*) ; 

int usb_gadget_unregister_driver (struct usb_gadget_driver *driver)
{
	unsigned long	flags;
	int		status = -ENODEV;

	if (!udc)
		return -ENODEV;
	if (!driver || driver != udc->driver || !driver->unbind)
		return -EINVAL;

	if (udc->dc_clk != NULL)
		omap_udc_enable_clock(1);

	if (machine_without_vbus_sense())
		omap_vbus_session(&udc->gadget, 0);

	if (udc->transceiver)
		(void) otg_set_peripheral(udc->transceiver, NULL);
	else
		pullup_disable(udc);

	spin_lock_irqsave(&udc->lock, flags);
	udc_quiesce(udc);
	spin_unlock_irqrestore(&udc->lock, flags);

	driver->unbind(&udc->gadget);
	udc->gadget.dev.driver = NULL;
	udc->driver = NULL;

	if (udc->dc_clk != NULL)
		omap_udc_enable_clock(0);
	DBG("unregistered driver '%s'\n", driver->driver.name);
	return status;
}