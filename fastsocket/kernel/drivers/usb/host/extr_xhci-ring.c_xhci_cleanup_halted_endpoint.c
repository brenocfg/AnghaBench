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
struct xhci_virt_ep {unsigned int stopped_stream; union xhci_trb* stopped_trb; struct xhci_td* stopped_td; int /*<<< orphan*/  ep_state; } ;
struct xhci_td {TYPE_2__* urb; } ;
struct xhci_hcd {TYPE_1__** devs; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct xhci_virt_ep* eps; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_HALTED ; 
 int /*<<< orphan*/  xhci_cleanup_stalled_ring (struct xhci_hcd*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  xhci_queue_reset_ep (struct xhci_hcd*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  xhci_ring_cmd_db (struct xhci_hcd*) ; 

__attribute__((used)) static void xhci_cleanup_halted_endpoint(struct xhci_hcd *xhci,
		unsigned int slot_id, unsigned int ep_index,
		unsigned int stream_id,
		struct xhci_td *td, union xhci_trb *event_trb)
{
	struct xhci_virt_ep *ep = &xhci->devs[slot_id]->eps[ep_index];
	ep->ep_state |= EP_HALTED;
	ep->stopped_td = td;
	ep->stopped_trb = event_trb;
	ep->stopped_stream = stream_id;

	xhci_queue_reset_ep(xhci, slot_id, ep_index);
	xhci_cleanup_stalled_ring(xhci, td->urb->dev, ep_index);

	ep->stopped_td = NULL;
	ep->stopped_trb = NULL;
	ep->stopped_stream = 0;

	xhci_ring_cmd_db(xhci);
}