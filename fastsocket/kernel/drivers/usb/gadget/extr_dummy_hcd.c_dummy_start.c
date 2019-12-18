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
struct TYPE_3__ {int otg_port; } ;
struct usb_hcd {int uses_new_polling; TYPE_1__ self; int /*<<< orphan*/  state; int /*<<< orphan*/  power_budget; } ;
struct TYPE_4__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct dummy {int /*<<< orphan*/  urbp_list; int /*<<< orphan*/  rh_state; TYPE_2__ timer; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMMY_RH_RUNNING ; 
 int /*<<< orphan*/  HC_STATE_RUNNING ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POWER_BUDGET ; 
 int /*<<< orphan*/  dev_attr_urbs ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dummy_dev (struct dummy*) ; 
 int /*<<< orphan*/  dummy_timer ; 
 struct dummy* hcd_to_dummy (struct usb_hcd*) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dummy_start (struct usb_hcd *hcd)
{
	struct dummy		*dum;

	dum = hcd_to_dummy (hcd);

	/*
	 * MASTER side init ... we emulate a root hub that'll only ever
	 * talk to one device (the slave side).  Also appears in sysfs,
	 * just like more familiar pci-based HCDs.
	 */
	spin_lock_init (&dum->lock);
	init_timer (&dum->timer);
	dum->timer.function = dummy_timer;
	dum->timer.data = (unsigned long) dum;
	dum->rh_state = DUMMY_RH_RUNNING;

	INIT_LIST_HEAD (&dum->urbp_list);

	hcd->power_budget = POWER_BUDGET;
	hcd->state = HC_STATE_RUNNING;
	hcd->uses_new_polling = 1;

#ifdef CONFIG_USB_OTG
	hcd->self.otg_port = 1;
#endif

	/* FIXME 'urbs' should be a per-device thing, maybe in usbcore */
	return device_create_file (dummy_dev(dum), &dev_attr_urbs);
}