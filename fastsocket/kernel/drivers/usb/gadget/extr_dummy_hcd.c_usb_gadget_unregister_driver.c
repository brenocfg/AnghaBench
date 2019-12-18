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
struct usb_gadget_driver {int /*<<< orphan*/  (* unbind ) (TYPE_3__*) ;TYPE_1__ driver; } ;
struct TYPE_5__ {int /*<<< orphan*/ * driver; } ;
struct TYPE_6__ {TYPE_2__ dev; } ;
struct dummy {int /*<<< orphan*/  lock; scalar_t__ pullup; struct usb_gadget_driver* driver; TYPE_3__ gadget; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dummy_to_hcd (struct dummy*) ; 
 int /*<<< orphan*/  set_link_state (struct dummy*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 struct dummy* the_controller ; 
 int /*<<< orphan*/  udc_dev (struct dummy*) ; 
 int /*<<< orphan*/  usb_hcd_poll_rh_status (int /*<<< orphan*/ ) ; 

int
usb_gadget_unregister_driver (struct usb_gadget_driver *driver)
{
	struct dummy	*dum = the_controller;
	unsigned long	flags;

	if (!dum)
		return -ENODEV;
	if (!driver || driver != dum->driver || !driver->unbind)
		return -EINVAL;

	dev_dbg (udc_dev(dum), "unregister gadget driver '%s'\n",
			driver->driver.name);

	spin_lock_irqsave (&dum->lock, flags);
	dum->pullup = 0;
	set_link_state (dum);
	spin_unlock_irqrestore (&dum->lock, flags);

	driver->unbind (&dum->gadget);
	dum->gadget.dev.driver = NULL;
	dum->driver = NULL;

	spin_lock_irqsave (&dum->lock, flags);
	dum->pullup = 0;
	set_link_state (dum);
	spin_unlock_irqrestore (&dum->lock, flags);

	usb_hcd_poll_rh_status (dummy_to_hcd (dum));
	return 0;
}