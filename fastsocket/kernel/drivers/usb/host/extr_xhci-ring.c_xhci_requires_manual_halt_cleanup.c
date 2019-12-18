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
struct xhci_hcd {int dummy; } ;
struct xhci_ep_ctx {int ep_info; } ;

/* Variables and functions */
 unsigned int COMP_BABBLE ; 
 unsigned int COMP_SPLIT_ERR ; 
 unsigned int COMP_TX_ERR ; 
 int /*<<< orphan*/  EP_STATE_HALTED ; 
 int /*<<< orphan*/  EP_STATE_MASK ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xhci_requires_manual_halt_cleanup(struct xhci_hcd *xhci,
		struct xhci_ep_ctx *ep_ctx,
		unsigned int trb_comp_code)
{
	/* TRB completion codes that may require a manual halt cleanup */
	if (trb_comp_code == COMP_TX_ERR ||
			trb_comp_code == COMP_BABBLE ||
			trb_comp_code == COMP_SPLIT_ERR)
		/* The 0.96 spec says a babbling control endpoint
		 * is not halted. The 0.96 spec says it is.  Some HW
		 * claims to be 0.95 compliant, but it halts the control
		 * endpoint anyway.  Check if a babble halted the
		 * endpoint.
		 */
		if ((ep_ctx->ep_info & cpu_to_le32(EP_STATE_MASK)) ==
		    cpu_to_le32(EP_STATE_HALTED))
			return 1;

	return 0;
}