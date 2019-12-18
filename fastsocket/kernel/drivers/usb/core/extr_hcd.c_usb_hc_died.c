#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  root_hub; int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; int /*<<< orphan*/  flags; scalar_t__ rh_registered; struct usb_hcd* shared_hcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCD_FLAG_DEAD ; 
 int /*<<< orphan*/  HCD_FLAG_POLL_RH ; 
 int /*<<< orphan*/  HCD_FLAG_RH_RUNNING ; 
 int /*<<< orphan*/  USB_STATE_NOTATTACHED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hcd_root_hub_lock ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ usb_hcd_is_primary_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_kick_khubd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_device_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void usb_hc_died (struct usb_hcd *hcd)
{
	unsigned long flags;

	dev_err (hcd->self.controller, "HC died; cleaning up\n");

	spin_lock_irqsave (&hcd_root_hub_lock, flags);
	clear_bit(HCD_FLAG_RH_RUNNING, &hcd->flags);
	set_bit(HCD_FLAG_DEAD, &hcd->flags);
	if (hcd->rh_registered) {
		clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);

		/* make khubd clean up old urbs and devices */
		usb_set_device_state (hcd->self.root_hub,
				USB_STATE_NOTATTACHED);
		usb_kick_khubd (hcd->self.root_hub);
	}
	if (usb_hcd_is_primary_hcd(hcd) && hcd->shared_hcd) {
		hcd = hcd->shared_hcd;
		if (hcd->rh_registered) {
			clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);

			/* make khubd clean up old urbs and devices */
			usb_set_device_state(hcd->self.root_hub,
					USB_STATE_NOTATTACHED);
			usb_kick_khubd(hcd->self.root_hub);
		}
	}
	spin_unlock_irqrestore (&hcd_root_hub_lock, flags);
	/* Make sure that the other roothub is also deallocated. */
}