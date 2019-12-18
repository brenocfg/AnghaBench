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
typedef  scalar_t__ u32 ;
struct xhci_hcd {TYPE_1__* run_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rsvd; int /*<<< orphan*/  microframe_index; } ;

/* Variables and functions */
 scalar_t__ XHCI_INIT_VALUE ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,TYPE_1__*,...) ; 
 scalar_t__ xhci_readl (struct xhci_hcd*,int /*<<< orphan*/ *) ; 

void xhci_print_run_regs(struct xhci_hcd *xhci)
{
	u32 temp;
	int i;

	xhci_dbg(xhci, "xHCI runtime registers at %p:\n", xhci->run_regs);
	temp = xhci_readl(xhci, &xhci->run_regs->microframe_index);
	xhci_dbg(xhci, "  %p: Microframe index = 0x%x\n",
			&xhci->run_regs->microframe_index,
			(unsigned int) temp);
	for (i = 0; i < 7; ++i) {
		temp = xhci_readl(xhci, &xhci->run_regs->rsvd[i]);
		if (temp != XHCI_INIT_VALUE)
			xhci_dbg(xhci, "  WARN: %p: Rsvd[%i] = 0x%x\n",
					&xhci->run_regs->rsvd[i],
					i, (unsigned int) temp);
	}
}