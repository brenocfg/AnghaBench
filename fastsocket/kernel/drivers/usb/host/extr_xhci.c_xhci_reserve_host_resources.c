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
struct xhci_hcd {scalar_t__ num_active_eps; scalar_t__ limit_active_eps; } ;
struct xhci_container_ctx {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ xhci_count_num_new_endpoints (struct xhci_hcd*,struct xhci_container_ctx*) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,scalar_t__,scalar_t__,...) ; 

__attribute__((used)) static int xhci_reserve_host_resources(struct xhci_hcd *xhci,
		struct xhci_container_ctx *in_ctx)
{
	u32 added_eps;

	added_eps = xhci_count_num_new_endpoints(xhci, in_ctx);
	if (xhci->num_active_eps + added_eps > xhci->limit_active_eps) {
		xhci_dbg(xhci, "Not enough ep ctxs: "
				"%u active, need to add %u, limit is %u.\n",
				xhci->num_active_eps, added_eps,
				xhci->limit_active_eps);
		return -ENOMEM;
	}
	xhci->num_active_eps += added_eps;
	xhci_dbg(xhci, "Adding %u ep ctxs, %u now active.\n", added_eps,
			xhci->num_active_eps);
	return 0;
}