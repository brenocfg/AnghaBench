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
struct xhci_hcd {int /*<<< orphan*/  hcc_params; } ;
struct xhci_ep_ctx {int /*<<< orphan*/ * reserved; int /*<<< orphan*/  tx_info; int /*<<< orphan*/  deq; int /*<<< orphan*/  ep_info2; int /*<<< orphan*/  ep_info; } ;
struct xhci_container_ctx {scalar_t__ bytes; scalar_t__ dma; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int HCC_64BYTE_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_rsvd64 (struct xhci_hcd*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,int,...) ; 
 struct xhci_ep_ctx* xhci_get_ep_ctx (struct xhci_hcd*,struct xhci_container_ctx*,int) ; 

__attribute__((used)) static void xhci_dbg_ep_ctx(struct xhci_hcd *xhci,
		     struct xhci_container_ctx *ctx,
		     unsigned int last_ep)
{
	int i, j;
	int last_ep_ctx = 31;
	/* Fields are 32 bits wide, DMA addresses are in bytes */
	int field_size = 32 / 8;
	int csz = HCC_64BYTE_CONTEXT(xhci->hcc_params);

	if (last_ep < 31)
		last_ep_ctx = last_ep + 1;
	for (i = 0; i < last_ep_ctx; ++i) {
		struct xhci_ep_ctx *ep_ctx = xhci_get_ep_ctx(xhci, ctx, i);
		dma_addr_t dma = ctx->dma +
			((unsigned long)ep_ctx - (unsigned long)ctx->bytes);

		xhci_dbg(xhci, "Endpoint %02d Context:\n", i);
		xhci_dbg(xhci, "@%p (virt) @%08llx (dma) %#08x - ep_info\n",
				&ep_ctx->ep_info,
				(unsigned long long)dma, ep_ctx->ep_info);
		dma += field_size;
		xhci_dbg(xhci, "@%p (virt) @%08llx (dma) %#08x - ep_info2\n",
				&ep_ctx->ep_info2,
				(unsigned long long)dma, ep_ctx->ep_info2);
		dma += field_size;
		xhci_dbg(xhci, "@%p (virt) @%08llx (dma) %#08llx - deq\n",
				&ep_ctx->deq,
				(unsigned long long)dma, ep_ctx->deq);
		dma += 2*field_size;
		xhci_dbg(xhci, "@%p (virt) @%08llx (dma) %#08x - tx_info\n",
				&ep_ctx->tx_info,
				(unsigned long long)dma, ep_ctx->tx_info);
		dma += field_size;
		for (j = 0; j < 3; ++j) {
			xhci_dbg(xhci, "@%p (virt) @%08llx (dma) %#08x - rsvd[%d]\n",
					&ep_ctx->reserved[j],
					(unsigned long long)dma,
					ep_ctx->reserved[j], j);
			dma += field_size;
		}

		if (csz)
			dbg_rsvd64(xhci, (u64 *)ep_ctx, dma);
	}
}