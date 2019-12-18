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
struct xhci_ring {scalar_t__ first_seg; } ;
struct xhci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct xhci_ring*) ; 
 int /*<<< orphan*/  xhci_free_segments_for_ring (struct xhci_hcd*,scalar_t__) ; 

void xhci_ring_free(struct xhci_hcd *xhci, struct xhci_ring *ring)
{
	if (!ring)
		return;

	if (ring->first_seg)
		xhci_free_segments_for_ring(xhci, ring->first_seg);

	kfree(ring);
}