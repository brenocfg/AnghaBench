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
struct usb_hcd {int dummy; } ;
struct ohci_hcd {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  control; int /*<<< orphan*/  intrdisable; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI_INTR_MIE ; 
 struct ohci_hcd* hcd_to_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/  ohci_readl (struct ohci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci_usb_reset (struct ohci_hcd*) ; 
 int /*<<< orphan*/  ohci_writel (struct ohci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ohci_shutdown (struct usb_hcd *hcd)
{
	struct ohci_hcd *ohci;

	ohci = hcd_to_ohci (hcd);
	ohci_writel (ohci, OHCI_INTR_MIE, &ohci->regs->intrdisable);
	ohci_usb_reset (ohci);
	/* flush the writes */
	(void) ohci_readl (ohci, &ohci->regs->control);
}