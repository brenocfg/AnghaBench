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
struct xhci_segment {struct xhci_segment* next; TYPE_2__* trbs; } ;
struct xhci_ring {int type; int /*<<< orphan*/  td_list; struct xhci_segment* first_seg; } ;
struct xhci_hcd {int dummy; } ;
typedef  enum xhci_ring_type { ____Placeholder_xhci_ring_type } xhci_ring_type ;
struct TYPE_3__ {int /*<<< orphan*/  control; } ;
struct TYPE_4__ {TYPE_1__ link; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int TRBS_PER_SEGMENT ; 
 int /*<<< orphan*/  TRB_CYCLE ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xhci_initialize_ring_info (struct xhci_ring*,unsigned int) ; 
 int /*<<< orphan*/  xhci_link_segments (struct xhci_hcd*,struct xhci_segment*,struct xhci_segment*,int) ; 

__attribute__((used)) static void xhci_reinit_cached_ring(struct xhci_hcd *xhci,
			struct xhci_ring *ring, unsigned int cycle_state,
			enum xhci_ring_type type)
{
	struct xhci_segment	*seg = ring->first_seg;
	int i;

	do {
		memset(seg->trbs, 0,
				sizeof(union xhci_trb)*TRBS_PER_SEGMENT);
		if (cycle_state == 0) {
			for (i = 0; i < TRBS_PER_SEGMENT; i++)
				seg->trbs[i].link.control |= TRB_CYCLE;
		}
		/* All endpoint rings have link TRBs */
		xhci_link_segments(xhci, seg, seg->next, type);
		seg = seg->next;
	} while (seg != ring->first_seg);
	ring->type = type;
	xhci_initialize_ring_info(ring, cycle_state);
	/* td list should be empty since all URBs have been cancelled,
	 * but just in case...
	 */
	INIT_LIST_HEAD(&ring->td_list);
}