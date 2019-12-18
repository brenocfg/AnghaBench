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
typedef  scalar_t__ u32 ;
struct xhci_hcd {int /*<<< orphan*/  num_active_eps; } ;
struct xhci_container_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ xhci_count_num_new_endpoints (struct xhci_hcd*,struct xhci_container_ctx*) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xhci_free_host_resources(struct xhci_hcd *xhci,
		struct xhci_container_ctx *in_ctx)
{
	u32 num_failed_eps;

	num_failed_eps = xhci_count_num_new_endpoints(xhci, in_ctx);
	xhci->num_active_eps -= num_failed_eps;
	xhci_dbg(xhci, "Removing %u failed ep ctxs, %u now active.\n",
			num_failed_eps,
			xhci->num_active_eps);
}