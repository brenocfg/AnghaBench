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
struct TYPE_2__ {int control; } ;
union xhci_trb {TYPE_1__ link; } ;
struct xhci_segment {scalar_t__ next; union xhci_trb* trbs; } ;
struct xhci_ring {scalar_t__ first_seg; } ;
struct xhci_hcd {struct xhci_ring* event_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_TOGGLE ; 
 size_t TRBS_PER_SEGMENT ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool last_trb_on_last_seg(struct xhci_hcd *xhci, struct xhci_ring *ring,
		struct xhci_segment *seg, union xhci_trb *trb)
{
	if (ring == xhci->event_ring)
		return (trb == &seg->trbs[TRBS_PER_SEGMENT]) &&
			(seg->next == xhci->event_ring->first_seg);
	else
		return trb->link.control & cpu_to_le32(LINK_TOGGLE);
}