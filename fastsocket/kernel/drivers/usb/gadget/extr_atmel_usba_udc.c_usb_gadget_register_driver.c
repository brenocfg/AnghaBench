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
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_6__ {TYPE_2__ dev; } ;
struct usba_udc {int devstatus; scalar_t__ vbus_prev; TYPE_3__ gadget; struct usb_gadget_driver* driver; int /*<<< orphan*/  lock; int /*<<< orphan*/  vbus_pin; int /*<<< orphan*/  hclk; int /*<<< orphan*/  pclk; int /*<<< orphan*/  pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct usb_gadget_driver {int (* bind ) (TYPE_3__*) ;TYPE_1__ driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DBG_ERR ; 
 int /*<<< orphan*/  DBG_GADGET ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  INT_ENB ; 
 int /*<<< orphan*/  USBA_ENABLE_MASK ; 
 int /*<<< orphan*/  USBA_END_OF_RESET ; 
 int USB_DEVICE_SELF_POWERED ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (TYPE_3__*) ; 
 struct usba_udc the_udc ; 
 int /*<<< orphan*/  toggle_bias (int) ; 
 int /*<<< orphan*/  usba_writel (struct usba_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vbus_is_present (struct usba_udc*) ; 

int usb_gadget_register_driver(struct usb_gadget_driver *driver)
{
	struct usba_udc *udc = &the_udc;
	unsigned long flags;
	int ret;

	if (!udc->pdev)
		return -ENODEV;

	spin_lock_irqsave(&udc->lock, flags);
	if (udc->driver) {
		spin_unlock_irqrestore(&udc->lock, flags);
		return -EBUSY;
	}

	udc->devstatus = 1 << USB_DEVICE_SELF_POWERED;
	udc->driver = driver;
	udc->gadget.dev.driver = &driver->driver;
	spin_unlock_irqrestore(&udc->lock, flags);

	clk_enable(udc->pclk);
	clk_enable(udc->hclk);

	ret = driver->bind(&udc->gadget);
	if (ret) {
		DBG(DBG_ERR, "Could not bind to driver %s: error %d\n",
			driver->driver.name, ret);
		goto err_driver_bind;
	}

	DBG(DBG_GADGET, "registered driver `%s'\n", driver->driver.name);

	udc->vbus_prev = 0;
	if (gpio_is_valid(udc->vbus_pin))
		enable_irq(gpio_to_irq(udc->vbus_pin));

	/* If Vbus is present, enable the controller and wait for reset */
	spin_lock_irqsave(&udc->lock, flags);
	if (vbus_is_present(udc) && udc->vbus_prev == 0) {
		toggle_bias(1);
		usba_writel(udc, CTRL, USBA_ENABLE_MASK);
		usba_writel(udc, INT_ENB, USBA_END_OF_RESET);
	}
	spin_unlock_irqrestore(&udc->lock, flags);

	return 0;

err_driver_bind:
	udc->driver = NULL;
	udc->gadget.dev.driver = NULL;
	return ret;
}