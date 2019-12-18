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
struct xhci_hcd {int /*<<< orphan*/  device_pool; int /*<<< orphan*/  hcc_params; } ;
struct xhci_container_ctx {int type; int size; int /*<<< orphan*/  bytes; int /*<<< orphan*/  dma; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CTX_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ HCC_64BYTE_CONTEXT (int /*<<< orphan*/ ) ; 
 int XHCI_CTX_TYPE_DEVICE ; 
 int XHCI_CTX_TYPE_INPUT ; 
 int /*<<< orphan*/  dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct xhci_container_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct xhci_container_ctx *xhci_alloc_container_ctx(struct xhci_hcd *xhci,
						    int type, gfp_t flags)
{
	struct xhci_container_ctx *ctx = kzalloc(sizeof(*ctx), flags);
	if (!ctx)
		return NULL;

	BUG_ON((type != XHCI_CTX_TYPE_DEVICE) && (type != XHCI_CTX_TYPE_INPUT));
	ctx->type = type;
	ctx->size = HCC_64BYTE_CONTEXT(xhci->hcc_params) ? 2048 : 1024;
	if (type == XHCI_CTX_TYPE_INPUT)
		ctx->size += CTX_SIZE(xhci->hcc_params);

	ctx->bytes = dma_pool_alloc(xhci->device_pool, flags, &ctx->dma);
	memset(ctx->bytes, 0, ctx->size);
	return ctx;
}