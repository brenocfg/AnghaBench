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
struct xhci_ring {unsigned int cycle_state; int num_trbs_free; int num_segs; scalar_t__ deq_updates; scalar_t__ enq_updates; TYPE_1__* first_seg; TYPE_1__* deq_seg; int /*<<< orphan*/  enqueue; int /*<<< orphan*/  dequeue; TYPE_1__* enq_seg; } ;
struct TYPE_2__ {int /*<<< orphan*/  trbs; } ;

/* Variables and functions */
 int TRBS_PER_SEGMENT ; 

__attribute__((used)) static void xhci_initialize_ring_info(struct xhci_ring *ring,
					unsigned int cycle_state)
{
	/* The ring is empty, so the enqueue pointer == dequeue pointer */
	ring->enqueue = ring->first_seg->trbs;
	ring->enq_seg = ring->first_seg;
	ring->dequeue = ring->enqueue;
	ring->deq_seg = ring->first_seg;
	/* The ring is initialized to 0. The producer must write 1 to the cycle
	 * bit to handover ownership of the TRB, so PCS = 1.  The consumer must
	 * compare CCS to the cycle bit to check ownership, so CCS = 1.
	 *
	 * New rings are initialized with cycle state equal to 1; if we are
	 * handling ring expansion, set the cycle state equal to the old ring.
	 */
	ring->cycle_state = cycle_state;
	/* Not necessary for new rings, but needed for re-initialized rings */
	ring->enq_updates = 0;
	ring->deq_updates = 0;

	/*
	 * Each segment has a link TRB, and leave an extra TRB for SW
	 * accounting purpose
	 */
	ring->num_trbs_free = ring->num_segs * (TRBS_PER_SEGMENT - 1) - 1;
}