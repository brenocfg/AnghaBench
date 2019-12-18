#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xhci_generic_trb {int* field; } ;
union xhci_trb {struct xhci_generic_trb generic; } ;
struct xhci_segment {struct xhci_segment* next; union xhci_trb* trbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_TOGGLE ; 
 int TRBS_PER_SEGMENT ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xhci_segment *find_trb_seg(
		struct xhci_segment *start_seg,
		union xhci_trb	*trb, int *cycle_state)
{
	struct xhci_segment *cur_seg = start_seg;
	struct xhci_generic_trb *generic_trb;

	while (cur_seg->trbs > trb ||
			&cur_seg->trbs[TRBS_PER_SEGMENT - 1] < trb) {
		generic_trb = &cur_seg->trbs[TRBS_PER_SEGMENT - 1].generic;
		if (generic_trb->field[3] & cpu_to_le32(LINK_TOGGLE))
			*cycle_state ^= 0x1;
		cur_seg = cur_seg->next;
		if (cur_seg == start_seg)
			/* Looped over the entire list.  Oops! */
			return NULL;
	}
	return cur_seg;
}