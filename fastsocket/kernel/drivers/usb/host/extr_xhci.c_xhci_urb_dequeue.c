#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_12__ {scalar_t__ expires; } ;
struct xhci_virt_ep {int ep_state; TYPE_6__ stop_cmd_timer; int /*<<< orphan*/  stop_cmds_pending; int /*<<< orphan*/  cancelled_td_list; } ;
struct xhci_td {int /*<<< orphan*/  cancelled_td_list; int /*<<< orphan*/  first_trb; int /*<<< orphan*/  start_seg; int /*<<< orphan*/  td_list; } ;
struct xhci_ring {int dummy; } ;
struct xhci_hcd {int xhc_state; int /*<<< orphan*/  lock; TYPE_2__** devs; TYPE_1__* op_regs; } ;
struct usb_hcd {int dummy; } ;
struct urb_priv {int td_cnt; int length; struct xhci_td** td; } ;
struct urb {TYPE_4__* dev; TYPE_3__* ep; struct urb_priv* hcpriv; } ;
struct TYPE_11__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_10__ {size_t slot_id; int /*<<< orphan*/  devpath; } ;
struct TYPE_9__ {TYPE_5__ desc; } ;
struct TYPE_8__ {struct xhci_virt_ep* eps; } ;
struct TYPE_7__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EINVAL ; 
 int EP_HALT_PENDING ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 int HZ ; 
 int XHCI_STATE_DYING ; 
 int XHCI_STATE_HALTED ; 
 int XHCI_STOP_EP_CMD_TIMEOUT ; 
 int /*<<< orphan*/  add_timer (TYPE_6__*) ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_hcd_check_unlink_urb (struct usb_hcd*,struct urb*,int) ; 
 int /*<<< orphan*/  usb_hcd_giveback_urb (struct usb_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (struct usb_hcd*,struct urb*) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,...) ; 
 unsigned int xhci_get_endpoint_index (TYPE_5__*) ; 
 int /*<<< orphan*/  xhci_queue_stop_endpoint (struct xhci_hcd*,size_t,unsigned int,int /*<<< orphan*/ ) ; 
 int xhci_readl (struct xhci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_ring_cmd_db (struct xhci_hcd*) ; 
 scalar_t__ xhci_trb_virt_to_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_urb_free_priv (struct xhci_hcd*,struct urb_priv*) ; 
 struct xhci_ring* xhci_urb_to_transfer_ring (struct xhci_hcd*,struct urb*) ; 

int xhci_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	unsigned long flags;
	int ret, i;
	u32 temp;
	struct xhci_hcd *xhci;
	struct urb_priv	*urb_priv;
	struct xhci_td *td;
	unsigned int ep_index;
	struct xhci_ring *ep_ring;
	struct xhci_virt_ep *ep;

	xhci = hcd_to_xhci(hcd);
	spin_lock_irqsave(&xhci->lock, flags);
	/* Make sure the URB hasn't completed or been unlinked already */
	ret = usb_hcd_check_unlink_urb(hcd, urb, status);
	if (ret || !urb->hcpriv)
		goto done;
	temp = xhci_readl(xhci, &xhci->op_regs->status);
	if (temp == 0xffffffff || (xhci->xhc_state & XHCI_STATE_HALTED)) {
		xhci_dbg(xhci, "HW died, freeing TD.\n");
		urb_priv = urb->hcpriv;
		for (i = urb_priv->td_cnt; i < urb_priv->length; i++) {
			td = urb_priv->td[i];
			if (!list_empty(&td->td_list))
				list_del_init(&td->td_list);
			if (!list_empty(&td->cancelled_td_list))
				list_del_init(&td->cancelled_td_list);
		}

		usb_hcd_unlink_urb_from_ep(hcd, urb);
		spin_unlock_irqrestore(&xhci->lock, flags);
		usb_hcd_giveback_urb(hcd, urb, -ESHUTDOWN);
		xhci_urb_free_priv(xhci, urb_priv);
		return ret;
	}
	if ((xhci->xhc_state & XHCI_STATE_DYING) ||
			(xhci->xhc_state & XHCI_STATE_HALTED)) {
		xhci_dbg(xhci, "Ep 0x%x: URB %p to be canceled on "
				"non-responsive xHCI host.\n",
				urb->ep->desc.bEndpointAddress, urb);
		/* Let the stop endpoint command watchdog timer (which set this
		 * state) finish cleaning up the endpoint TD lists.  We must
		 * have caught it in the middle of dropping a lock and giving
		 * back an URB.
		 */
		goto done;
	}

	ep_index = xhci_get_endpoint_index(&urb->ep->desc);
	ep = &xhci->devs[urb->dev->slot_id]->eps[ep_index];
	ep_ring = xhci_urb_to_transfer_ring(xhci, urb);
	if (!ep_ring) {
		ret = -EINVAL;
		goto done;
	}

	urb_priv = urb->hcpriv;
	i = urb_priv->td_cnt;
	if (i < urb_priv->length)
		xhci_dbg(xhci, "Cancel URB %p, dev %s, ep 0x%x, "
				"starting at offset 0x%llx\n",
				urb, urb->dev->devpath,
				urb->ep->desc.bEndpointAddress,
				(unsigned long long) xhci_trb_virt_to_dma(
					urb_priv->td[i]->start_seg,
					urb_priv->td[i]->first_trb));

	for (; i < urb_priv->length; i++) {
		td = urb_priv->td[i];
		list_add_tail(&td->cancelled_td_list, &ep->cancelled_td_list);
	}

	/* Queue a stop endpoint command, but only if this is
	 * the first cancellation to be handled.
	 */
	if (!(ep->ep_state & EP_HALT_PENDING)) {
		ep->ep_state |= EP_HALT_PENDING;
		ep->stop_cmds_pending++;
		ep->stop_cmd_timer.expires = jiffies +
			XHCI_STOP_EP_CMD_TIMEOUT * HZ;
		add_timer(&ep->stop_cmd_timer);
		xhci_queue_stop_endpoint(xhci, urb->dev->slot_id, ep_index, 0);
		xhci_ring_cmd_db(xhci);
	}
done:
	spin_unlock_irqrestore(&xhci->lock, flags);
	return ret;
}