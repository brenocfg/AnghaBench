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
struct usb_hcd {int dummy; } ;
struct urb_priv {int /*<<< orphan*/  node; struct uhci_qh* qh; } ;
struct urb {int /*<<< orphan*/  error_count; TYPE_1__* ep; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * next; } ;
struct uhci_qh {int type; scalar_t__ state; int /*<<< orphan*/  is_stopped; TYPE_2__ queue; } ;
struct uhci_hcd {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_3__ {struct uhci_qh* hcpriv; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ QH_STATE_IDLE ; 
#define  USB_ENDPOINT_XFER_BULK 131 
#define  USB_ENDPOINT_XFER_CONTROL 130 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 
 struct uhci_hcd* hcd_to_uhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uhci_activate_qh (struct uhci_hcd*,struct uhci_qh*) ; 
 struct uhci_qh* uhci_alloc_qh (struct uhci_hcd*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct urb_priv* uhci_alloc_urb_priv (struct uhci_hcd*,struct urb*) ; 
 int /*<<< orphan*/  uhci_free_urb_priv (struct uhci_hcd*,struct urb_priv*) ; 
 int /*<<< orphan*/  uhci_make_qh_idle (struct uhci_hcd*,struct uhci_qh*) ; 
 int uhci_submit_bulk (struct uhci_hcd*,struct urb*,struct uhci_qh*) ; 
 int uhci_submit_control (struct uhci_hcd*,struct urb*,struct uhci_qh*) ; 
 int uhci_submit_interrupt (struct uhci_hcd*,struct urb*,struct uhci_qh*) ; 
 int uhci_submit_isochronous (struct uhci_hcd*,struct urb*,struct uhci_qh*) ; 
 int /*<<< orphan*/  uhci_urbp_wants_fsbr (struct uhci_hcd*,struct urb_priv*) ; 
 int usb_hcd_link_urb_to_ep (struct usb_hcd*,struct urb*) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (struct usb_hcd*,struct urb*) ; 

__attribute__((used)) static int uhci_urb_enqueue(struct usb_hcd *hcd,
		struct urb *urb, gfp_t mem_flags)
{
	int ret;
	struct uhci_hcd *uhci = hcd_to_uhci(hcd);
	unsigned long flags;
	struct urb_priv *urbp;
	struct uhci_qh *qh;

	spin_lock_irqsave(&uhci->lock, flags);

	ret = usb_hcd_link_urb_to_ep(hcd, urb);
	if (ret)
		goto done_not_linked;

	ret = -ENOMEM;
	urbp = uhci_alloc_urb_priv(uhci, urb);
	if (!urbp)
		goto done;

	if (urb->ep->hcpriv)
		qh = urb->ep->hcpriv;
	else {
		qh = uhci_alloc_qh(uhci, urb->dev, urb->ep);
		if (!qh)
			goto err_no_qh;
	}
	urbp->qh = qh;

	switch (qh->type) {
	case USB_ENDPOINT_XFER_CONTROL:
		ret = uhci_submit_control(uhci, urb, qh);
		break;
	case USB_ENDPOINT_XFER_BULK:
		ret = uhci_submit_bulk(uhci, urb, qh);
		break;
	case USB_ENDPOINT_XFER_INT:
		ret = uhci_submit_interrupt(uhci, urb, qh);
		break;
	case USB_ENDPOINT_XFER_ISOC:
		urb->error_count = 0;
		ret = uhci_submit_isochronous(uhci, urb, qh);
		break;
	}
	if (ret != 0)
		goto err_submit_failed;

	/* Add this URB to the QH */
	list_add_tail(&urbp->node, &qh->queue);

	/* If the new URB is the first and only one on this QH then either
	 * the QH is new and idle or else it's unlinked and waiting to
	 * become idle, so we can activate it right away.  But only if the
	 * queue isn't stopped. */
	if (qh->queue.next == &urbp->node && !qh->is_stopped) {
		uhci_activate_qh(uhci, qh);
		uhci_urbp_wants_fsbr(uhci, urbp);
	}
	goto done;

err_submit_failed:
	if (qh->state == QH_STATE_IDLE)
		uhci_make_qh_idle(uhci, qh);	/* Reclaim unused QH */
err_no_qh:
	uhci_free_urb_priv(uhci, urbp);
done:
	if (ret)
		usb_hcd_unlink_urb_from_ep(hcd, urb);
done_not_linked:
	spin_unlock_irqrestore(&uhci->lock, flags);
	return ret;
}