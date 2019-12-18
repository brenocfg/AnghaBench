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
struct TYPE_4__ {int /*<<< orphan*/  speed; } ;
struct usba_udc {int vbus_prev; int /*<<< orphan*/  lock; TYPE_2__ gadget; TYPE_1__* driver; int /*<<< orphan*/  vbus_pin; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* disconnect ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  INT_ENB ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  USBA_DISABLE_MASK ; 
 int /*<<< orphan*/  USBA_ENABLE_MASK ; 
 int /*<<< orphan*/  USBA_END_OF_RESET ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_all_endpoints (struct usba_udc*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  toggle_bias (int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usba_writel (struct usba_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t usba_vbus_irq(int irq, void *devid)
{
	struct usba_udc *udc = devid;
	int vbus;

	/* debounce */
	udelay(10);

	spin_lock(&udc->lock);

	/* May happen if Vbus pin toggles during probe() */
	if (!udc->driver)
		goto out;

	vbus = gpio_get_value(udc->vbus_pin);
	if (vbus != udc->vbus_prev) {
		if (vbus) {
			toggle_bias(1);
			usba_writel(udc, CTRL, USBA_ENABLE_MASK);
			usba_writel(udc, INT_ENB, USBA_END_OF_RESET);
		} else {
			udc->gadget.speed = USB_SPEED_UNKNOWN;
			reset_all_endpoints(udc);
			toggle_bias(0);
			usba_writel(udc, CTRL, USBA_DISABLE_MASK);
			if (udc->driver->disconnect) {
				spin_unlock(&udc->lock);
				udc->driver->disconnect(&udc->gadget);
				spin_lock(&udc->lock);
			}
		}
		udc->vbus_prev = vbus;
	}

out:
	spin_unlock(&udc->lock);

	return IRQ_HANDLED;
}