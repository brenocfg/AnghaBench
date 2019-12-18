#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xhci_virt_ep {scalar_t__ stopped_stream; int /*<<< orphan*/ * stopped_trb; int /*<<< orphan*/ * stopped_td; } ;
struct xhci_hcd {int /*<<< orphan*/  lock; TYPE_1__** devs; } ;
struct TYPE_5__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_host_endpoint {TYPE_2__ desc; scalar_t__ hcpriv; } ;
struct usb_hcd {int dummy; } ;
struct usb_device {size_t slot_id; } ;
struct TYPE_4__ {struct xhci_virt_ep* eps; } ;

/* Variables and functions */
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ usb_endpoint_xfer_control (TYPE_2__*) ; 
 int /*<<< orphan*/  xhci_cleanup_stalled_ring (struct xhci_hcd*,struct usb_device*,unsigned int) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,...) ; 
 unsigned int xhci_get_endpoint_index (TYPE_2__*) ; 
 int xhci_queue_reset_ep (struct xhci_hcd*,size_t,unsigned int) ; 
 int /*<<< orphan*/  xhci_ring_cmd_db (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*) ; 

void xhci_endpoint_reset(struct usb_hcd *hcd,
		struct usb_host_endpoint *ep)
{
	struct xhci_hcd *xhci;
	struct usb_device *udev;
	unsigned int ep_index;
	unsigned long flags;
	int ret;
	struct xhci_virt_ep *virt_ep;

	xhci = hcd_to_xhci(hcd);
	udev = (struct usb_device *) ep->hcpriv;
	/* Called with a root hub endpoint (or an endpoint that wasn't added
	 * with xhci_add_endpoint()
	 */
	if (!ep->hcpriv)
		return;
	ep_index = xhci_get_endpoint_index(&ep->desc);
	virt_ep = &xhci->devs[udev->slot_id]->eps[ep_index];
	if (!virt_ep->stopped_td) {
		xhci_dbg(xhci, "Endpoint 0x%x not halted, refusing to reset.\n",
				ep->desc.bEndpointAddress);
		return;
	}
	if (usb_endpoint_xfer_control(&ep->desc)) {
		xhci_dbg(xhci, "Control endpoint stall already handled.\n");
		return;
	}

	xhci_dbg(xhci, "Queueing reset endpoint command\n");
	spin_lock_irqsave(&xhci->lock, flags);
	ret = xhci_queue_reset_ep(xhci, udev->slot_id, ep_index);
	/*
	 * Can't change the ring dequeue pointer until it's transitioned to the
	 * stopped state, which is only upon a successful reset endpoint
	 * command.  Better hope that last command worked!
	 */
	if (!ret) {
		xhci_cleanup_stalled_ring(xhci, udev, ep_index);
		kfree(virt_ep->stopped_td);
		xhci_ring_cmd_db(xhci);
	}
	virt_ep->stopped_td = NULL;
	virt_ep->stopped_trb = NULL;
	virt_ep->stopped_stream = 0;
	spin_unlock_irqrestore(&xhci->lock, flags);

	if (ret)
		xhci_warn(xhci, "FIXME allocate a new ring segment\n");
}