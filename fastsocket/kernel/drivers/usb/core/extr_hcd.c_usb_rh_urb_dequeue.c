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
struct usb_hcd {struct urb* status_urb; int /*<<< orphan*/  rh_timer; int /*<<< orphan*/  uses_new_polling; } ;
struct urb {TYPE_1__* ep; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hcd_root_hub_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ usb_endpoint_num (int /*<<< orphan*/ *) ; 
 int usb_hcd_check_unlink_urb (struct usb_hcd*,struct urb*,int) ; 
 int /*<<< orphan*/  usb_hcd_giveback_urb (struct usb_hcd*,struct urb*,int) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (struct usb_hcd*,struct urb*) ; 

__attribute__((used)) static int usb_rh_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	unsigned long	flags;
	int		rc;

	spin_lock_irqsave(&hcd_root_hub_lock, flags);
	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	if (rc)
		goto done;

	if (usb_endpoint_num(&urb->ep->desc) == 0) {	/* Control URB */
		;	/* Do nothing */

	} else {				/* Status URB */
		if (!hcd->uses_new_polling)
			del_timer (&hcd->rh_timer);
		if (urb == hcd->status_urb) {
			hcd->status_urb = NULL;
			usb_hcd_unlink_urb_from_ep(hcd, urb);

			spin_unlock(&hcd_root_hub_lock);
			usb_hcd_giveback_urb(hcd, urb, status);
			spin_lock(&hcd_root_hub_lock);
		}
	}
 done:
	spin_unlock_irqrestore(&hcd_root_hub_lock, flags);
	return rc;
}