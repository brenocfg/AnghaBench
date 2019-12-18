#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * driver; } ;
struct TYPE_7__ {TYPE_1__ dev; int /*<<< orphan*/  speed; } ;
struct usba_udc {int /*<<< orphan*/  pclk; int /*<<< orphan*/  hclk; struct usb_gadget_driver* driver; TYPE_3__ gadget; int /*<<< orphan*/  lock; int /*<<< orphan*/  vbus_pin; int /*<<< orphan*/  pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct usb_gadget_driver {TYPE_2__ driver; int /*<<< orphan*/  (* unbind ) (TYPE_3__*) ;int /*<<< orphan*/  (* disconnect ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_GADGET ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  USBA_DISABLE_MASK ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_all_endpoints (struct usba_udc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 struct usba_udc the_udc ; 
 int /*<<< orphan*/  toggle_bias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usba_writel (struct usba_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int usb_gadget_unregister_driver(struct usb_gadget_driver *driver)
{
	struct usba_udc *udc = &the_udc;
	unsigned long flags;

	if (!udc->pdev)
		return -ENODEV;
	if (driver != udc->driver || !driver->unbind)
		return -EINVAL;

	if (gpio_is_valid(udc->vbus_pin))
		disable_irq(gpio_to_irq(udc->vbus_pin));

	spin_lock_irqsave(&udc->lock, flags);
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	reset_all_endpoints(udc);
	spin_unlock_irqrestore(&udc->lock, flags);

	/* This will also disable the DP pullup */
	toggle_bias(0);
	usba_writel(udc, CTRL, USBA_DISABLE_MASK);

	if (udc->driver->disconnect)
		udc->driver->disconnect(&udc->gadget);

	driver->unbind(&udc->gadget);
	udc->gadget.dev.driver = NULL;
	udc->driver = NULL;

	clk_disable(udc->hclk);
	clk_disable(udc->pclk);

	DBG(DBG_GADGET, "unregistered driver `%s'\n", driver->driver.name);

	return 0;
}