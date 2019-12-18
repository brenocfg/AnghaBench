#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xhci_ring {scalar_t__ type; int cycle_state; int /*<<< orphan*/  dequeue; TYPE_1__* deq_seg; int /*<<< orphan*/  num_trbs_free; int /*<<< orphan*/  deq_updates; } ;
struct xhci_hcd {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  trbs; struct TYPE_4__* next; } ;

/* Variables and functions */
 scalar_t__ TYPE_EVENT ; 
 scalar_t__ last_trb (struct xhci_hcd*,struct xhci_ring*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ last_trb_on_last_seg (struct xhci_hcd*,struct xhci_ring*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ xhci_trb_virt_to_dma (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inc_deq(struct xhci_hcd *xhci, struct xhci_ring *ring)
{
	unsigned long long addr;

	ring->deq_updates++;

	/*
	 * If this is not event ring, and the dequeue pointer
	 * is not on a link TRB, there is one more usable TRB
	 */
	if (ring->type != TYPE_EVENT &&
			!last_trb(xhci, ring, ring->deq_seg, ring->dequeue))
		ring->num_trbs_free++;

	do {
		/*
		 * Update the dequeue pointer further if that was a link TRB or
		 * we're at the end of an event ring segment (which doesn't have
		 * link TRBS)
		 */
		if (last_trb(xhci, ring, ring->deq_seg, ring->dequeue)) {
			if (ring->type == TYPE_EVENT &&
					last_trb_on_last_seg(xhci, ring,
						ring->deq_seg, ring->dequeue)) {
				ring->cycle_state = (ring->cycle_state ? 0 : 1);
			}
			ring->deq_seg = ring->deq_seg->next;
			ring->dequeue = ring->deq_seg->trbs;
		} else {
			ring->dequeue++;
		}
	} while (last_trb(xhci, ring, ring->deq_seg, ring->dequeue));

	addr = (unsigned long long) xhci_trb_virt_to_dma(ring->deq_seg, ring->dequeue);
}