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
struct ohci_hcd {TYPE_1__* regs; int /*<<< orphan*/  hc_control; } ;
struct TYPE_2__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI_CTRL_RWC ; 
 int /*<<< orphan*/  ohci_readl (struct ohci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci_writel (struct ohci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ohci_usb_reset (struct ohci_hcd *ohci)
{
	ohci->hc_control = ohci_readl (ohci, &ohci->regs->control);
	ohci->hc_control &= OHCI_CTRL_RWC;
	ohci_writel (ohci, ohci->hc_control, &ohci->regs->control);
}