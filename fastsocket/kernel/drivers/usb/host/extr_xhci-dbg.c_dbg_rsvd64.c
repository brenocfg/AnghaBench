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
typedef  int /*<<< orphan*/  u64 ;
struct xhci_hcd {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,int /*<<< orphan*/ *,unsigned long long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dbg_rsvd64(struct xhci_hcd *xhci, u64 *ctx, dma_addr_t dma)
{
	int i;
	for (i = 0; i < 4; ++i) {
		xhci_dbg(xhci, "@%p (virt) @%08llx "
			 "(dma) %#08llx - rsvd64[%d]\n",
			 &ctx[4 + i], (unsigned long long)dma,
			 ctx[4 + i], i);
		dma += 8;
	}
}