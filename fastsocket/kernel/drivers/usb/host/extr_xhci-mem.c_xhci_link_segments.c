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
typedef  int /*<<< orphan*/  u32 ;
struct xhci_segment {TYPE_2__* trbs; int /*<<< orphan*/  dma; struct xhci_segment* next; } ;
struct xhci_hcd {int quirks; } ;
typedef  enum xhci_ring_type { ____Placeholder_xhci_ring_type } xhci_ring_type ;
struct TYPE_3__ {int /*<<< orphan*/  control; int /*<<< orphan*/  segment_ptr; } ;
struct TYPE_4__ {TYPE_1__ link; } ;

/* Variables and functions */
 int TRBS_PER_SEGMENT ; 
 int /*<<< orphan*/  TRB_CHAIN ; 
 int /*<<< orphan*/  TRB_LINK ; 
 int /*<<< orphan*/  TRB_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRB_TYPE_BITMASK ; 
 int TYPE_EVENT ; 
 int TYPE_ISOC ; 
 int XHCI_AMD_0x96_HOST ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ xhci_link_trb_quirk (struct xhci_hcd*) ; 

__attribute__((used)) static void xhci_link_segments(struct xhci_hcd *xhci, struct xhci_segment *prev,
		struct xhci_segment *next, enum xhci_ring_type type)
{
	u32 val;

	if (!prev || !next)
		return;
	prev->next = next;
	if (type != TYPE_EVENT) {
		prev->trbs[TRBS_PER_SEGMENT-1].link.segment_ptr =
			cpu_to_le64(next->dma);

		/* Set the last TRB in the segment to have a TRB type ID of Link TRB */
		val = le32_to_cpu(prev->trbs[TRBS_PER_SEGMENT-1].link.control);
		val &= ~TRB_TYPE_BITMASK;
		val |= TRB_TYPE(TRB_LINK);
		/* Always set the chain bit with 0.95 hardware */
		/* Set chain bit for isoc rings on AMD 0.96 host */
		if (xhci_link_trb_quirk(xhci) ||
				(type == TYPE_ISOC &&
				 (xhci->quirks & XHCI_AMD_0x96_HOST)))
			val |= TRB_CHAIN;
		prev->trbs[TRBS_PER_SEGMENT-1].link.control = cpu_to_le32(val);
	}
}