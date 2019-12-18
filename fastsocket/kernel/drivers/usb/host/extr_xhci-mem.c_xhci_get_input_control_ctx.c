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
struct xhci_input_control_ctx {int dummy; } ;
struct xhci_hcd {int dummy; } ;
struct xhci_container_ctx {scalar_t__ type; scalar_t__ bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ XHCI_CTX_TYPE_INPUT ; 

struct xhci_input_control_ctx *xhci_get_input_control_ctx(struct xhci_hcd *xhci,
					      struct xhci_container_ctx *ctx)
{
	BUG_ON(ctx->type != XHCI_CTX_TYPE_INPUT);
	return (struct xhci_input_control_ctx *)ctx->bytes;
}