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
struct usb_gadget_driver {int /*<<< orphan*/  (* unbind ) (TYPE_2__*) ;int /*<<< orphan*/  function; } ;
struct TYPE_5__ {int /*<<< orphan*/ * driver; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;
struct musb {int /*<<< orphan*/  lock; scalar_t__ is_active; TYPE_2__ g; struct usb_gadget_driver* gadget_driver; TYPE_3__* xceiv; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OTG_STATE_UNDEFINED ; 
 scalar_t__ is_otg_enabled (struct musb*) ; 
 int /*<<< orphan*/  musb_gadget_vbus_draw (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_hnp_stop (struct musb*) ; 
 int /*<<< orphan*/  musb_platform_try_idle (struct musb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_to_hcd (struct musb*) ; 
 int /*<<< orphan*/  otg_set_peripheral (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stop_activity (struct musb*,struct usb_gadget_driver*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 struct musb* the_gadget ; 
 int /*<<< orphan*/  usb_remove_hcd (int /*<<< orphan*/ ) ; 

int usb_gadget_unregister_driver(struct usb_gadget_driver *driver)
{
	unsigned long	flags;
	int		retval = 0;
	struct musb	*musb = the_gadget;

	if (!driver || !driver->unbind || !musb)
		return -EINVAL;

	/* REVISIT always use otg_set_peripheral() here too;
	 * this needs to shut down the OTG engine.
	 */

	spin_lock_irqsave(&musb->lock, flags);

#ifdef	CONFIG_USB_MUSB_OTG
	musb_hnp_stop(musb);
#endif

	if (musb->gadget_driver == driver) {

		(void) musb_gadget_vbus_draw(&musb->g, 0);

		musb->xceiv->state = OTG_STATE_UNDEFINED;
		stop_activity(musb, driver);
		otg_set_peripheral(musb->xceiv, NULL);

		DBG(3, "unregistering driver %s\n", driver->function);
		spin_unlock_irqrestore(&musb->lock, flags);
		driver->unbind(&musb->g);
		spin_lock_irqsave(&musb->lock, flags);

		musb->gadget_driver = NULL;
		musb->g.dev.driver = NULL;

		musb->is_active = 0;
		musb_platform_try_idle(musb, 0);
	} else
		retval = -EINVAL;
	spin_unlock_irqrestore(&musb->lock, flags);

	if (is_otg_enabled(musb) && retval == 0) {
		usb_remove_hcd(musb_to_hcd(musb));
		/* FIXME we need to be able to register another
		 * gadget driver here and have everything work;
		 * that currently misbehaves.
		 */
	}

	return retval;
}