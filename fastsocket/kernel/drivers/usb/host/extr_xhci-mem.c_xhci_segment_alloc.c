#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xhci_segment {int /*<<< orphan*/ * next; int /*<<< orphan*/  dma; TYPE_2__* trbs; } ;
struct xhci_hcd {int /*<<< orphan*/  segment_pool; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  control; } ;
struct TYPE_5__ {TYPE_1__ link; } ;

/* Variables and functions */
 int TRBS_PER_SEGMENT ; 
 int /*<<< orphan*/  TRB_CYCLE ; 
 int /*<<< orphan*/  TRB_SEGMENT_SIZE ; 
 TYPE_2__* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct xhci_segment*) ; 
 struct xhci_segment* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xhci_segment *xhci_segment_alloc(struct xhci_hcd *xhci,
					unsigned int cycle_state, gfp_t flags)
{
	struct xhci_segment *seg;
	dma_addr_t	dma;
	int		i;

	seg = kzalloc(sizeof *seg, flags);
	if (!seg)
		return NULL;

	seg->trbs = dma_pool_alloc(xhci->segment_pool, flags, &dma);
	if (!seg->trbs) {
		kfree(seg);
		return NULL;
	}

	memset(seg->trbs, 0, TRB_SEGMENT_SIZE);
	/* If the cycle state is 0, set the cycle bit to 1 for all the TRBs */
	if (cycle_state == 0) {
		for (i = 0; i < TRBS_PER_SEGMENT; i++)
			seg->trbs[i].link.control |= TRB_CYCLE;
	}
	seg->dma = dma;
	seg->next = NULL;

	return seg;
}