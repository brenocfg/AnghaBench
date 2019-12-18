#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xhci_stream_ctx {int dummy; } ;
struct xhci_hcd {int /*<<< orphan*/  medium_streams_pool; int /*<<< orphan*/  small_streams_pool; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  controller; } ;
struct TYPE_4__ {TYPE_1__ self; } ;

/* Variables and functions */
 unsigned int MEDIUM_STREAM_ARRAY_SIZE ; 
 unsigned int SMALL_STREAM_ARRAY_SIZE ; 
 struct xhci_stream_ctx* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct xhci_stream_ctx* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 TYPE_2__* xhci_to_hcd (struct xhci_hcd*) ; 

__attribute__((used)) static struct xhci_stream_ctx *xhci_alloc_stream_ctx(struct xhci_hcd *xhci,
		unsigned int num_stream_ctxs, dma_addr_t *dma,
		gfp_t mem_flags)
{
	struct pci_dev *pdev = to_pci_dev(xhci_to_hcd(xhci)->self.controller);

	if (num_stream_ctxs > MEDIUM_STREAM_ARRAY_SIZE)
		return dma_alloc_coherent(&pdev->dev,
				sizeof(struct xhci_stream_ctx)*num_stream_ctxs,
				dma, mem_flags);
	else if (num_stream_ctxs <= SMALL_STREAM_ARRAY_SIZE)
		return dma_pool_alloc(xhci->small_streams_pool,
				mem_flags, dma);
	else
		return dma_pool_alloc(xhci->medium_streams_pool,
				mem_flags, dma);
}