#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * bus; } ;
struct usb_gadget_driver {int (* bind ) (TYPE_5__*) ;scalar_t__ speed; TYPE_3__ driver; int /*<<< orphan*/  setup; } ;
struct TYPE_6__ {int maxpacket; int /*<<< orphan*/  ep_list; int /*<<< orphan*/ * ops; scalar_t__ name; } ;
struct dummy_ep {TYPE_1__ ep; int /*<<< orphan*/  queue; int /*<<< orphan*/ * desc; TYPE_5__* gadget; int /*<<< orphan*/  last_io; scalar_t__ setup_stage; scalar_t__ already_seen; scalar_t__ wedged; scalar_t__ halted; } ;
struct TYPE_9__ {TYPE_3__* driver; } ;
struct TYPE_10__ {TYPE_4__ dev; TYPE_1__* ep0; int /*<<< orphan*/  ep_list; } ;
struct TYPE_7__ {int /*<<< orphan*/  queue; } ;
struct dummy {int pullup; int /*<<< orphan*/  lock; TYPE_5__ gadget; struct usb_gadget_driver* driver; TYPE_2__ fifo_req; struct dummy_ep* ep; scalar_t__ devstatus; } ;

/* Variables and functions */
 int DUMMY_ENDPOINTS ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dummy_ep_ops ; 
 int /*<<< orphan*/  dummy_to_hcd (struct dummy*) ; 
 scalar_t__* ep_name ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_link_state (struct dummy*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_5__*) ; 
 struct dummy* the_controller ; 
 int /*<<< orphan*/  udc_dev (struct dummy*) ; 
 int /*<<< orphan*/  usb_hcd_poll_rh_status (int /*<<< orphan*/ ) ; 

int
usb_gadget_register_driver (struct usb_gadget_driver *driver)
{
	struct dummy	*dum = the_controller;
	int		retval, i;

	if (!dum)
		return -EINVAL;
	if (dum->driver)
		return -EBUSY;
	if (!driver->bind || !driver->setup
			|| driver->speed == USB_SPEED_UNKNOWN)
		return -EINVAL;

	/*
	 * SLAVE side init ... the layer above hardware, which
	 * can't enumerate without help from the driver we're binding.
	 */

	dum->devstatus = 0;

	INIT_LIST_HEAD (&dum->gadget.ep_list);
	for (i = 0; i < DUMMY_ENDPOINTS; i++) {
		struct dummy_ep	*ep = &dum->ep [i];

		if (!ep_name [i])
			break;
		ep->ep.name = ep_name [i];
		ep->ep.ops = &dummy_ep_ops;
		list_add_tail (&ep->ep.ep_list, &dum->gadget.ep_list);
		ep->halted = ep->wedged = ep->already_seen =
				ep->setup_stage = 0;
		ep->ep.maxpacket = ~0;
		ep->last_io = jiffies;
		ep->gadget = &dum->gadget;
		ep->desc = NULL;
		INIT_LIST_HEAD (&ep->queue);
	}

	dum->gadget.ep0 = &dum->ep [0].ep;
	dum->ep [0].ep.maxpacket = 64;
	list_del_init (&dum->ep [0].ep.ep_list);
	INIT_LIST_HEAD(&dum->fifo_req.queue);

	driver->driver.bus = NULL;
	dum->driver = driver;
	dum->gadget.dev.driver = &driver->driver;
	dev_dbg (udc_dev(dum), "binding gadget driver '%s'\n",
			driver->driver.name);
	retval = driver->bind(&dum->gadget);
	if (retval) {
		dum->driver = NULL;
		dum->gadget.dev.driver = NULL;
		return retval;
	}

	/* khubd will enumerate this in a while */
	spin_lock_irq (&dum->lock);
	dum->pullup = 1;
	set_link_state (dum);
	spin_unlock_irq (&dum->lock);

	usb_hcd_poll_rh_status (dummy_to_hcd (dum));
	return 0;
}