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
struct xhci_segment {struct xhci_segment* next; } ;
struct xhci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xhci_segment_free (struct xhci_hcd*,struct xhci_segment*) ; 

__attribute__((used)) static void xhci_free_segments_for_ring(struct xhci_hcd *xhci,
				struct xhci_segment *first)
{
	struct xhci_segment *seg;

	seg = first->next;
	while (seg != first) {
		struct xhci_segment *next = seg->next;
		xhci_segment_free(xhci, seg);
		seg = next;
	}
	xhci_segment_free(xhci, first);
}