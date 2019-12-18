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

/* Variables and functions */
 int /*<<< orphan*/  xhci_print_cap_regs (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_print_op_regs (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_print_ports (struct xhci_hcd*) ; 

void xhci_print_registers(struct xhci_hcd *xhci)
{
	xhci_print_cap_regs(xhci);
	xhci_print_op_regs(xhci);
	xhci_print_ports(xhci);
}