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
typedef  union xhci_trb {int dummy; } xhci_trb ;
typedef  int u32 ;
struct xhci_virt_ep {int dummy; } ;
struct xhci_virt_device {int /*<<< orphan*/  out_ctx; } ;
struct xhci_transfer_event {int /*<<< orphan*/  transfer_len; int /*<<< orphan*/  buffer; int /*<<< orphan*/  flags; } ;
struct xhci_td {TYPE_1__* urb; union xhci_trb* last_trb; } ;
struct xhci_ring {union xhci_trb* dequeue; } ;
struct xhci_hcd {struct xhci_virt_device** devs; } ;
struct xhci_ep_ctx {int dummy; } ;
struct TYPE_2__ {int transfer_flags; scalar_t__ actual_length; void* transfer_buffer_length; } ;

/* Variables and functions */
#define  COMP_SHORT_TX 132 
#define  COMP_STALL 131 
#define  COMP_STOP 130 
#define  COMP_STOP_INVAL 129 
#define  COMP_SUCCESS 128 
 int EINPROGRESS ; 
 int EREMOTEIO ; 
 int ESHUTDOWN ; 
 void* EVENT_TRB_LEN (int /*<<< orphan*/ ) ; 
 int GET_COMP_CODE (int /*<<< orphan*/ ) ; 
 int TRB_TO_EP_ID (int /*<<< orphan*/ ) ; 
 unsigned int TRB_TO_SLOT_ID (int /*<<< orphan*/ ) ; 
 int URB_SHORT_NOT_OK ; 
 int finish_td (struct xhci_hcd*,struct xhci_td*,union xhci_trb*,struct xhci_transfer_event*,struct xhci_virt_ep*,int*,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_cleanup_halted_endpoint (struct xhci_hcd*,unsigned int,int,int /*<<< orphan*/ ,struct xhci_td*,union xhci_trb*) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,...) ; 
 struct xhci_ring* xhci_dma_to_transfer_ring (struct xhci_virt_ep*,int /*<<< orphan*/ ) ; 
 struct xhci_ep_ctx* xhci_get_ep_ctx (struct xhci_hcd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xhci_requires_manual_halt_cleanup (struct xhci_hcd*,struct xhci_ep_ctx*,int) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*) ; 

__attribute__((used)) static int process_ctrl_td(struct xhci_hcd *xhci, struct xhci_td *td,
	union xhci_trb *event_trb, struct xhci_transfer_event *event,
	struct xhci_virt_ep *ep, int *status)
{
	struct xhci_virt_device *xdev;
	struct xhci_ring *ep_ring;
	unsigned int slot_id;
	int ep_index;
	struct xhci_ep_ctx *ep_ctx;
	u32 trb_comp_code;

	slot_id = TRB_TO_SLOT_ID(le32_to_cpu(event->flags));
	xdev = xhci->devs[slot_id];
	ep_index = TRB_TO_EP_ID(le32_to_cpu(event->flags)) - 1;
	ep_ring = xhci_dma_to_transfer_ring(ep, le64_to_cpu(event->buffer));
	ep_ctx = xhci_get_ep_ctx(xhci, xdev->out_ctx, ep_index);
	trb_comp_code = GET_COMP_CODE(le32_to_cpu(event->transfer_len));

	switch (trb_comp_code) {
	case COMP_SUCCESS:
		if (event_trb == ep_ring->dequeue) {
			xhci_warn(xhci, "WARN: Success on ctrl setup TRB "
					"without IOC set??\n");
			*status = -ESHUTDOWN;
		} else if (event_trb != td->last_trb) {
			xhci_warn(xhci, "WARN: Success on ctrl data TRB "
					"without IOC set??\n");
			*status = -ESHUTDOWN;
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
	case COMP_STOP_INVAL:
	case COMP_STOP:
		return finish_td(xhci, td, event_trb, event, ep, status, false);
	default:
		if (!xhci_requires_manual_halt_cleanup(xhci,
					ep_ctx, trb_comp_code))
			break;
		xhci_dbg(xhci, "TRB error code %u, "
				"halted endpoint index = %u\n",
				trb_comp_code, ep_index);
		/* else fall through */
	case COMP_STALL:
		/* Did we transfer part of the data (middle) phase? */
		if (event_trb != ep_ring->dequeue &&
				event_trb != td->last_trb)
			td->urb->actual_length =
				td->urb->transfer_buffer_length -
				EVENT_TRB_LEN(le32_to_cpu(event->transfer_len));
		else
			td->urb->actual_length = 0;

		xhci_cleanup_halted_endpoint(xhci,
			slot_id, ep_index, 0, td, event_trb);
		return finish_td(xhci, td, event_trb, event, ep, status, true);
	}
	/*
	 * Did we transfer any data, despite the errors that might have
	 * happened?  I.e. did we get past the setup stage?
	 */
	if (event_trb != ep_ring->dequeue) {
		/* The event was for the status stage */
		if (event_trb == td->last_trb) {
			if (td->urb->actual_length != 0) {
				/* Don't overwrite a previously set error code
				 */
				if ((*status == -EINPROGRESS || *status == 0) &&
						(td->urb->transfer_flags
						 & URB_SHORT_NOT_OK))
					/* Did we already see a short data
					 * stage? */
					*status = -EREMOTEIO;
			} else {
				td->urb->actual_length =
					td->urb->transfer_buffer_length;
			}
		} else {
		/* Maybe the event was for the data stage? */
			td->urb->actual_length =
				td->urb->transfer_buffer_length -
				EVENT_TRB_LEN(le32_to_cpu(event->transfer_len));
			xhci_dbg(xhci, "Waiting for status "
					"stage event\n");
			return 0;
		}
	}

	return finish_td(xhci, td, event_trb, event, ep, status, false);
}