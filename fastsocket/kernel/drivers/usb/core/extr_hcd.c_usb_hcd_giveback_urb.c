#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_hcd {int /*<<< orphan*/  self; } ;
struct urb {int unlinked; int transfer_flags; scalar_t__ actual_length; scalar_t__ transfer_buffer_length; int status; int /*<<< orphan*/  reject; int /*<<< orphan*/  use_count; int /*<<< orphan*/  (* complete ) (struct urb*) ;int /*<<< orphan*/ * hcpriv; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int URB_SHORT_NOT_OK ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct urb*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unmap_urb_for_dma (struct usb_hcd*,struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb_queue ; 
 int /*<<< orphan*/  usb_put_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 
 int /*<<< orphan*/  usbmon_urb_complete (int /*<<< orphan*/ *,struct urb*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void usb_hcd_giveback_urb(struct usb_hcd *hcd, struct urb *urb, int status)
{
	urb->hcpriv = NULL;
	if (unlikely(urb->unlinked))
		status = urb->unlinked;
	else if (unlikely((urb->transfer_flags & URB_SHORT_NOT_OK) &&
			urb->actual_length < urb->transfer_buffer_length &&
			!status))
		status = -EREMOTEIO;

	unmap_urb_for_dma(hcd, urb);
	usbmon_urb_complete(&hcd->self, urb, status);
	usb_unanchor_urb(urb);

	/* pass ownership to the completion handler */
	urb->status = status;
	urb->complete (urb);
	atomic_dec (&urb->use_count);
	if (unlikely(atomic_read(&urb->reject)))
		wake_up (&usb_kill_urb_queue);
	usb_put_urb (urb);
}