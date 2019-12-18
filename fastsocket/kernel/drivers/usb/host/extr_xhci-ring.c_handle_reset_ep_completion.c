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
struct TYPE_5__ {int /*<<< orphan*/ * field; } ;
union xhci_trb {TYPE_1__ generic; } ;
struct xhci_hcd {int quirks; TYPE_4__** devs; } ;
struct xhci_event_cmd {int /*<<< orphan*/  status; } ;
struct TYPE_8__ {TYPE_3__* eps; TYPE_2__* in_ctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  ep_state; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_HALTED ; 
 int /*<<< orphan*/  GET_COMP_CODE (int /*<<< orphan*/ ) ; 
 unsigned int TRB_TO_EP_INDEX (int /*<<< orphan*/ ) ; 
 int TRB_TO_SLOT_ID (int /*<<< orphan*/ ) ; 
 int XHCI_RESET_EP_QUIRK ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_doorbell_for_active_rings (struct xhci_hcd*,int,unsigned int) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,...) ; 
 int /*<<< orphan*/  xhci_queue_configure_endpoint (struct xhci_hcd*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xhci_ring_cmd_db (struct xhci_hcd*) ; 

__attribute__((used)) static void handle_reset_ep_completion(struct xhci_hcd *xhci,
		struct xhci_event_cmd *event,
		union xhci_trb *trb)
{
	int slot_id;
	unsigned int ep_index;

	slot_id = TRB_TO_SLOT_ID(le32_to_cpu(trb->generic.field[3]));
	ep_index = TRB_TO_EP_INDEX(le32_to_cpu(trb->generic.field[3]));
	/* This command will only fail if the endpoint wasn't halted,
	 * but we don't care.
	 */
	xhci_dbg(xhci, "Ignoring reset ep completion code of %u\n",
		 GET_COMP_CODE(le32_to_cpu(event->status)));

	/* HW with the reset endpoint quirk needs to have a configure endpoint
	 * command complete before the endpoint can be used.  Queue that here
	 * because the HW can't handle two commands being queued in a row.
	 */
	if (xhci->quirks & XHCI_RESET_EP_QUIRK) {
		xhci_dbg(xhci, "Queueing configure endpoint command\n");
		xhci_queue_configure_endpoint(xhci,
				xhci->devs[slot_id]->in_ctx->dma, slot_id,
				false);
		xhci_ring_cmd_db(xhci);
	} else {
		/* Clear our internal halted state and restart the ring(s) */
		xhci->devs[slot_id]->eps[ep_index].ep_state &= ~EP_HALTED;
		ring_doorbell_for_active_rings(xhci, slot_id, ep_index);
	}
}