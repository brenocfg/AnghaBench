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
struct xhci_hcd {int /*<<< orphan*/  hcc_params; } ;
struct xhci_ep_ctx {int dummy; } ;
struct xhci_container_ctx {scalar_t__ type; scalar_t__ bytes; } ;

/* Variables and functions */
 unsigned int CTX_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ XHCI_CTX_TYPE_INPUT ; 

struct xhci_ep_ctx *xhci_get_ep_ctx(struct xhci_hcd *xhci,
				    struct xhci_container_ctx *ctx,
				    unsigned int ep_index)
{
	/* increment ep index by offset of start of ep ctx array */
	ep_index++;
	if (ctx->type == XHCI_CTX_TYPE_INPUT)
		ep_index++;

	return (struct xhci_ep_ctx *)
		(ctx->bytes + (ep_index * CTX_SIZE(xhci->hcc_params)));
}