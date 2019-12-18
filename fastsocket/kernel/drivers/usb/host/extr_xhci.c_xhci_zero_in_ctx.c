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
struct xhci_virt_device {int /*<<< orphan*/  in_ctx; } ;
struct xhci_slot_ctx {int /*<<< orphan*/  dev_info; } ;
struct xhci_input_control_ctx {scalar_t__ add_flags; scalar_t__ drop_flags; } ;
struct xhci_hcd {int dummy; } ;
struct xhci_ep_ctx {scalar_t__ tx_info; scalar_t__ deq; scalar_t__ ep_info2; scalar_t__ ep_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAST_CTX (int) ; 
 int /*<<< orphan*/  LAST_CTX_MASK ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct xhci_ep_ctx* xhci_get_ep_ctx (struct xhci_hcd*,int /*<<< orphan*/ ,int) ; 
 struct xhci_input_control_ctx* xhci_get_input_control_ctx (struct xhci_hcd*,int /*<<< orphan*/ ) ; 
 struct xhci_slot_ctx* xhci_get_slot_ctx (struct xhci_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xhci_zero_in_ctx(struct xhci_hcd *xhci, struct xhci_virt_device *virt_dev)
{
	struct xhci_input_control_ctx *ctrl_ctx;
	struct xhci_ep_ctx *ep_ctx;
	struct xhci_slot_ctx *slot_ctx;
	int i;

	/* When a device's add flag and drop flag are zero, any subsequent
	 * configure endpoint command will leave that endpoint's state
	 * untouched.  Make sure we don't leave any old state in the input
	 * endpoint contexts.
	 */
	ctrl_ctx = xhci_get_input_control_ctx(xhci, virt_dev->in_ctx);
	ctrl_ctx->drop_flags = 0;
	ctrl_ctx->add_flags = 0;
	slot_ctx = xhci_get_slot_ctx(xhci, virt_dev->in_ctx);
	slot_ctx->dev_info &= cpu_to_le32(~LAST_CTX_MASK);
	/* Endpoint 0 is always valid */
	slot_ctx->dev_info |= cpu_to_le32(LAST_CTX(1));
	for (i = 1; i < 31; ++i) {
		ep_ctx = xhci_get_ep_ctx(xhci, virt_dev->in_ctx, i);
		ep_ctx->ep_info = 0;
		ep_ctx->ep_info2 = 0;
		ep_ctx->deq = 0;
		ep_ctx->tx_info = 0;
	}
}