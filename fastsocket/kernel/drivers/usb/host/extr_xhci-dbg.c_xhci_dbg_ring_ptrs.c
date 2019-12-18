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
struct xhci_ring {int /*<<< orphan*/  enq_updates; int /*<<< orphan*/  enqueue; int /*<<< orphan*/  enq_seg; int /*<<< orphan*/  deq_updates; int /*<<< orphan*/  dequeue; int /*<<< orphan*/  deq_seg; } ;
struct xhci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ xhci_trb_virt_to_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xhci_dbg_ring_ptrs(struct xhci_hcd *xhci, struct xhci_ring *ring)
{
	xhci_dbg(xhci, "Ring deq = %p (virt), 0x%llx (dma)\n",
			ring->dequeue,
			(unsigned long long)xhci_trb_virt_to_dma(ring->deq_seg,
							    ring->dequeue));
	xhci_dbg(xhci, "Ring deq updated %u times\n",
			ring->deq_updates);
	xhci_dbg(xhci, "Ring enq = %p (virt), 0x%llx (dma)\n",
			ring->enqueue,
			(unsigned long long)xhci_trb_virt_to_dma(ring->enq_seg,
							    ring->enqueue));
	xhci_dbg(xhci, "Ring enq updated %u times\n",
			ring->enq_updates);
}