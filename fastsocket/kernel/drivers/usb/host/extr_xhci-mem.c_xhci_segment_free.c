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
struct xhci_segment {int /*<<< orphan*/ * trbs; int /*<<< orphan*/  dma; } ;
struct xhci_hcd {int /*<<< orphan*/  segment_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct xhci_segment*) ; 

__attribute__((used)) static void xhci_segment_free(struct xhci_hcd *xhci, struct xhci_segment *seg)
{
	if (seg->trbs) {
		dma_pool_free(xhci->segment_pool, seg->trbs, seg->dma);
		seg->trbs = NULL;
	}
	kfree(seg);
}