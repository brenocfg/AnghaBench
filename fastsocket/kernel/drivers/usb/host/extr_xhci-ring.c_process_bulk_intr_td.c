#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * field; } ;
union xhci_trb {TYPE_4__ generic; } ;
typedef  int u32 ;
struct xhci_virt_ep {int dummy; } ;
struct xhci_transfer_event {int /*<<< orphan*/  transfer_len; int /*<<< orphan*/  buffer; } ;
struct xhci_td {TYPE_3__* urb; union xhci_trb* last_trb; } ;
struct xhci_segment {int dummy; } ;
struct xhci_ring {struct xhci_segment* deq_seg; union xhci_trb* dequeue; } ;
struct xhci_hcd {int quirks; } ;
struct TYPE_7__ {int transfer_flags; scalar_t__ transfer_buffer_length; scalar_t__ actual_length; TYPE_2__* ep; } ;
struct TYPE_5__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_6__ {TYPE_1__ desc; } ;

/* Variables and functions */
#define  COMP_SHORT_TX 129 
 int COMP_STOP_INVAL ; 
#define  COMP_SUCCESS 128 
 int EINPROGRESS ; 
 int EREMOTEIO ; 
 scalar_t__ EVENT_TRB_LEN (int /*<<< orphan*/ ) ; 
 int GET_COMP_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TRB_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRB_TYPE_LINK_LE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRB_TYPE_NOOP_LE32 (int /*<<< orphan*/ ) ; 
 int URB_SHORT_NOT_OK ; 
 int XHCI_TRUST_TX_LENGTH ; 
 int finish_td (struct xhci_hcd*,struct xhci_td*,union xhci_trb*,struct xhci_transfer_event*,struct xhci_virt_ep*,int*,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_trb (struct xhci_hcd*,struct xhci_ring*,struct xhci_segment**,union xhci_trb**) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct xhci_ring* xhci_dma_to_transfer_ring (struct xhci_virt_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,...) ; 

__attribute__((used)) static int process_bulk_intr_td(struct xhci_hcd *xhci, struct xhci_td *td,
	union xhci_trb *event_trb, struct xhci_transfer_event *event,
	struct xhci_virt_ep *ep, int *status)
{
	struct xhci_ring *ep_ring;
	union xhci_trb *cur_trb;
	struct xhci_segment *cur_seg;
	u32 trb_comp_code;

	ep_ring = xhci_dma_to_transfer_ring(ep, le64_to_cpu(event->buffer));
	trb_comp_code = GET_COMP_CODE(le32_to_cpu(event->transfer_len));

	switch (trb_comp_code) {
	case COMP_SUCCESS:
		/* Double check that the HW transferred everything. */
		if (event_trb != td->last_trb ||
		    EVENT_TRB_LEN(le32_to_cpu(event->transfer_len)) != 0) {
			xhci_warn(xhci, "WARN Successful completion "
					"on short TX\n");
			if (td->urb->transfer_flags & URB_SHORT_NOT_OK)
				*status = -EREMOTEIO;
			else
				*status = 0;
			if ((xhci->quirks & XHCI_TRUST_TX_LENGTH))
				trb_comp_code = COMP_SHORT_TX;
		} else {
			*status = 0;
		}
		break;
	case COMP_SHORT_TX:
		if (td->urb->transfer_flags & URB_SHORT_NOT_OK)
			*status = -EREMOTEIO;
		else
			*status = 0;
		break;
	default:
		/* Others already handled above */
		break;
	}
	if (trb_comp_code == COMP_SHORT_TX)
		xhci_dbg(xhci, "ep %#x - asked for %d bytes, "
				"%d bytes untransferred\n",
				td->urb->ep->desc.bEndpointAddress,
				td->urb->transfer_buffer_length,
				EVENT_TRB_LEN(le32_to_cpu(event->transfer_len)));
	/* Fast path - was this the last TRB in the TD for this URB? */
	if (event_trb == td->last_trb) {
		if (EVENT_TRB_LEN(le32_to_cpu(event->transfer_len)) != 0) {
			td->urb->actual_length =
				td->urb->transfer_buffer_length -
				EVENT_TRB_LEN(le32_to_cpu(event->transfer_len));
			if (td->urb->transfer_buffer_length <
					td->urb->actual_length) {
				xhci_warn(xhci, "HC gave bad length "
						"of %d bytes left\n",
					  EVENT_TRB_LEN(le32_to_cpu(event->transfer_len)));
				td->urb->actual_length = 0;
				if (td->urb->transfer_flags & URB_SHORT_NOT_OK)
					*status = -EREMOTEIO;
				else
					*status = 0;
			}
			/* Don't overwrite a previously set error code */
			if (*status == -EINPROGRESS) {
				if (td->urb->transfer_flags & URB_SHORT_NOT_OK)
					*status = -EREMOTEIO;
				else
					*status = 0;
			}
		} else {
			td->urb->actual_length =
				td->urb->transfer_buffer_length;
			/* Ignore a short packet completion if the
			 * untransferred length was zero.
			 */
			if (*status == -EREMOTEIO)
				*status = 0;
		}
	} else {
		/* Slow path - walk the list, starting from the dequeue
		 * pointer, to get the actual length transferred.
		 */
		td->urb->actual_length = 0;
		for (cur_trb = ep_ring->dequeue, cur_seg = ep_ring->deq_seg;
				cur_trb != event_trb;
				next_trb(xhci, ep_ring, &cur_seg, &cur_trb)) {
			if (!TRB_TYPE_NOOP_LE32(cur_trb->generic.field[3]) &&
			    !TRB_TYPE_LINK_LE32(cur_trb->generic.field[3]))
				td->urb->actual_length +=
					TRB_LEN(le32_to_cpu(cur_trb->generic.field[2]));
		}
		/* If the ring didn't stop on a Link or No-op TRB, add
		 * in the actual bytes transferred from the Normal TRB
		 */
		if (trb_comp_code != COMP_STOP_INVAL)
			td->urb->actual_length +=
				TRB_LEN(le32_to_cpu(cur_trb->generic.field[2])) -
				EVENT_TRB_LEN(le32_to_cpu(event->transfer_len));
	}

	return finish_td(xhci, td, event_trb, event, ep, status, false);
}