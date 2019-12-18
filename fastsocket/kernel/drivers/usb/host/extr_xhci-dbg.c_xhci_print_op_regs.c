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
struct xhci_hcd {int /*<<< orphan*/  op_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_print_command_reg (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_print_status (struct xhci_hcd*) ; 

__attribute__((used)) static void xhci_print_op_regs(struct xhci_hcd *xhci)
{
	xhci_dbg(xhci, "xHCI operational registers at %p:\n", xhci->op_regs);
	xhci_print_command_reg(xhci);
	xhci_print_status(xhci);
}