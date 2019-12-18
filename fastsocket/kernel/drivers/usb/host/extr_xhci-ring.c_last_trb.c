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
struct TYPE_2__ {int /*<<< orphan*/  control; } ;
union xhci_trb {TYPE_1__ link; } ;
struct xhci_segment {union xhci_trb* trbs; } ;
struct xhci_ring {int dummy; } ;
struct xhci_hcd {struct xhci_ring* event_ring; } ;

/* Variables and functions */
 size_t TRBS_PER_SEGMENT ; 
 int TRB_TYPE_LINK_LE32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int last_trb(struct xhci_hcd *xhci, struct xhci_ring *ring,
		struct xhci_segment *seg, union xhci_trb *trb)
{
	if (ring == xhci->event_ring)
		return trb == &seg->trbs[TRBS_PER_SEGMENT];
	else
		return TRB_TYPE_LINK_LE32(trb->link.control);
}