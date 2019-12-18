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
typedef  union xhci_trb {int dummy; } xhci_trb ;
typedef  scalar_t__ u32 ;
struct xhci_virt_ep {int /*<<< orphan*/  stopped_stream; union xhci_trb* stopped_trb; struct xhci_td* stopped_td; } ;
struct xhci_virt_device {int /*<<< orphan*/  out_ctx; } ;
struct xhci_transfer_event {int /*<<< orphan*/  transfer_len; int /*<<< orphan*/  buffer; int /*<<< orphan*/  flags; } ;
struct xhci_td {scalar_t__ last_trb; int /*<<< orphan*/  cancelled_td_list; int /*<<< orphan*/  td_list; struct urb* urb; } ;
struct xhci_ring {scalar_t__ dequeue; int /*<<< orphan*/  stream_id; } ;
struct xhci_hcd {int quirks; struct xhci_virt_device** devs; } ;
struct xhci_ep_ctx {int dummy; } ;
struct urb_priv {scalar_t__ td_cnt; scalar_t__ length; } ;
struct urb {scalar_t__ actual_length; scalar_t__ transfer_buffer_length; int transfer_flags; int /*<<< orphan*/  pipe; struct urb_priv* hcpriv; } ;
struct TYPE_3__ {scalar_t__ bandwidth_isoc_reqs; } ;
struct TYPE_4__ {TYPE_1__ self; } ;

/* Variables and functions */
 scalar_t__ COMP_STALL ; 
 scalar_t__ COMP_STOP ; 
 scalar_t__ COMP_STOP_INVAL ; 
 int EREMOTEIO ; 
 scalar_t__ GET_COMP_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PIPE_ISOCHRONOUS ; 
 int TRB_TO_EP_ID (int /*<<< orphan*/ ) ; 
 unsigned int TRB_TO_SLOT_ID (int /*<<< orphan*/ ) ; 
 int URB_SHORT_NOT_OK ; 
 int XHCI_AMD_PLL_FIX ; 
 int /*<<< orphan*/  inc_deq (struct xhci_hcd*,struct xhci_ring*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_amd_quirk_pll_enable () ; 
 scalar_t__ usb_pipetype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_cleanup_halted_endpoint (struct xhci_hcd*,unsigned int,int,int /*<<< orphan*/ ,struct xhci_td*,union xhci_trb*) ; 
 struct xhci_ring* xhci_dma_to_transfer_ring (struct xhci_virt_ep*,int /*<<< orphan*/ ) ; 
 struct xhci_ep_ctx* xhci_get_ep_ctx (struct xhci_hcd*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xhci_requires_manual_halt_cleanup (struct xhci_hcd*,struct xhci_ep_ctx*,scalar_t__) ; 
 TYPE_2__* xhci_to_hcd (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int finish_td(struct xhci_hcd *xhci, struct xhci_td *td,
	union xhci_trb *event_trb, struct xhci_transfer_event *event,
	struct xhci_virt_ep *ep, int *status, bool skip)
{
	struct xhci_virt_device *xdev;
	struct xhci_ring *ep_ring;
	unsigned int slot_id;
	int ep_index;
	struct urb *urb = NULL;
	struct xhci_ep_ctx *ep_ctx;
	int ret = 0;
	struct urb_priv	*urb_priv;
	u32 trb_comp_code;

	slot_id = TRB_TO_SLOT_ID(le32_to_cpu(event->flags));
	xdev = xhci->devs[slot_id];
	ep_index = TRB_TO_EP_ID(le32_to_cpu(event->flags)) - 1;
	ep_ring = xhci_dma_to_transfer_ring(ep, le64_to_cpu(event->buffer));
	ep_ctx = xhci_get_ep_ctx(xhci, xdev->out_ctx, ep_index);
	trb_comp_code = GET_COMP_CODE(le32_to_cpu(event->transfer_len));

	if (skip)
		goto td_cleanup;

	if (trb_comp_code == COMP_STOP_INVAL ||
			trb_comp_code == COMP_STOP) {
		/* The Endpoint Stop Command completion will take care of any
		 * stopped TDs.  A stopped TD may be restarted, so don't update
		 * the ring dequeue pointer or take this TD off any lists yet.
		 */
		ep->stopped_td = td;
		ep->stopped_trb = event_trb;
		return 0;
	} else {
		if (trb_comp_code == COMP_STALL) {
			/* The transfer is completed from the driver's
			 * perspective, but we need to issue a set dequeue
			 * command for this stalled endpoint to move the dequeue
			 * pointer past the TD.  We can't do that here because
			 * the halt condition must be cleared first.  Let the
			 * USB class driver clear the stall later.
			 */
			ep->stopped_td = td;
			ep->stopped_trb = event_trb;
			ep->stopped_stream = ep_ring->stream_id;
		} else if (xhci_requires_manual_halt_cleanup(xhci,
					ep_ctx, trb_comp_code)) {
			/* Other types of errors halt the endpoint, but the
			 * class driver doesn't call usb_reset_endpoint() unless
			 * the error is -EPIPE.  Clear the halted status in the
			 * xHCI hardware manually.
			 */
			xhci_cleanup_halted_endpoint(xhci,
					slot_id, ep_index, ep_ring->stream_id,
					td, event_trb);
		} else {
			/* Update ring dequeue pointer */
			while (ep_ring->dequeue != td->last_trb)
				inc_deq(xhci, ep_ring);
			inc_deq(xhci, ep_ring);
		}

td_cleanup:
		/* Clean up the endpoint's TD list */
		urb = td->urb;
		urb_priv = urb->hcpriv;

		/* Do one last check of the actual transfer length.
		 * If the host controller said we transferred more data than
		 * the buffer length, urb->actual_length will be a very big
		 * number (since it's unsigned).  Play it safe and say we didn't
		 * transfer anything.
		 */
		if (urb->actual_length > urb->transfer_buffer_length) {
			xhci_warn(xhci, "URB transfer length is wrong, "
					"xHC issue? req. len = %u, "
					"act. len = %u\n",
					urb->transfer_buffer_length,
					urb->actual_length);
			urb->actual_length = 0;
			if (td->urb->transfer_flags & URB_SHORT_NOT_OK)
				*status = -EREMOTEIO;
			else
				*status = 0;
		}
		list_del_init(&td->td_list);
		/* Was this TD slated to be cancelled but completed anyway? */
		if (!list_empty(&td->cancelled_td_list))
			list_del_init(&td->cancelled_td_list);

		urb_priv->td_cnt++;
		/* Giveback the urb when all the tds are completed */
		if (urb_priv->td_cnt == urb_priv->length) {
			ret = 1;
			if (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS) {
				xhci_to_hcd(xhci)->self.bandwidth_isoc_reqs--;
				if (xhci_to_hcd(xhci)->self.bandwidth_isoc_reqs
					== 0) {
					if (xhci->quirks & XHCI_AMD_PLL_FIX)
						usb_amd_quirk_pll_enable();
				}
			}
		}
	}

	return ret;
}