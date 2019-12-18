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
typedef  int /*<<< orphan*/  u32 ;
struct xhci_hcd {int /*<<< orphan*/  xhc_state; TYPE_1__* op_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RUN ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  STS_HALT ; 
 int /*<<< orphan*/  XHCI_MAX_HALT_USEC ; 
 int /*<<< orphan*/  XHCI_STATE_HALTED ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_err (struct xhci_hcd*,char*,int /*<<< orphan*/ ) ; 
 int xhci_handshake (struct xhci_hcd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_readl (struct xhci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_writel (struct xhci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xhci_start(struct xhci_hcd *xhci)
{
	u32 temp;
	int ret;

	temp = xhci_readl(xhci, &xhci->op_regs->command);
	temp |= (CMD_RUN);
	xhci_dbg(xhci, "// Turn on HC, cmd = 0x%x.\n",
			temp);
	xhci_writel(xhci, temp, &xhci->op_regs->command);

	/*
	 * Wait for the HCHalted Status bit to be 0 to indicate the host is
	 * running.
	 */
	ret = xhci_handshake(xhci, &xhci->op_regs->status,
			STS_HALT, 0, XHCI_MAX_HALT_USEC);
	if (ret == -ETIMEDOUT)
		xhci_err(xhci, "Host took too long to start, "
				"waited %u microseconds.\n",
				XHCI_MAX_HALT_USEC);
	if (!ret)
		xhci->xhc_state &= ~XHCI_STATE_HALTED;
	return ret;
}