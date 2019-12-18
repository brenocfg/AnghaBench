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
struct xhci_hcd {int /*<<< orphan*/  device_pool; } ;
struct xhci_container_ctx {int /*<<< orphan*/  dma; int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct xhci_container_ctx*) ; 

__attribute__((used)) static void xhci_free_container_ctx(struct xhci_hcd *xhci,
			     struct xhci_container_ctx *ctx)
{
	if (!ctx)
		return;
	dma_pool_free(xhci->device_pool, ctx->bytes, ctx->dma);
	kfree(ctx);
}