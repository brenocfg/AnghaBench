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
struct TYPE_2__ {int /*<<< orphan*/  control; int /*<<< orphan*/  intr_target; int /*<<< orphan*/  segment_ptr; } ;
union xhci_trb {TYPE_1__ link; } ;
typedef  int u64 ;
struct xhci_segment {int dma; union xhci_trb* trbs; } ;
struct xhci_hcd {int dummy; } ;

/* Variables and functions */
 int TRBS_PER_SEGMENT ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xhci_debug_segment(struct xhci_hcd *xhci, struct xhci_segment *seg)
{
	int i;
	u64 addr = seg->dma;
	union xhci_trb *trb = seg->trbs;

	for (i = 0; i < TRBS_PER_SEGMENT; ++i) {
		trb = &seg->trbs[i];
		xhci_dbg(xhci, "@%016llx %08x %08x %08x %08x\n", addr,
			 lower_32_bits(le64_to_cpu(trb->link.segment_ptr)),
			 upper_32_bits(le64_to_cpu(trb->link.segment_ptr)),
			 le32_to_cpu(trb->link.intr_target),
			 le32_to_cpu(trb->link.control));
		addr += sizeof(*trb);
	}
}