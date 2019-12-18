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
struct xhci_virt_ep {TYPE_1__* ring; } ;
struct xhci_hcd {int dummy; } ;
struct xhci_ep_ctx {int /*<<< orphan*/  deq; int /*<<< orphan*/  ep_info; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int cycle_state; int /*<<< orphan*/  dequeue; int /*<<< orphan*/  deq_seg; } ;

/* Variables and functions */
 int EP_HAS_LSA ; 
 int EP_MAXPSTREAMS_MASK ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int xhci_trb_virt_to_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xhci_setup_no_streams_ep_input_ctx(struct xhci_hcd *xhci,
		struct xhci_ep_ctx *ep_ctx,
		struct xhci_virt_ep *ep)
{
	dma_addr_t addr;
	ep_ctx->ep_info &= cpu_to_le32(~(EP_MAXPSTREAMS_MASK | EP_HAS_LSA));
	addr = xhci_trb_virt_to_dma(ep->ring->deq_seg, ep->ring->dequeue);
	ep_ctx->deq  = cpu_to_le64(addr | ep->ring->cycle_state);
}