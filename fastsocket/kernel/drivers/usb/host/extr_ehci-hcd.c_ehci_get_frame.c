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
struct ehci_hcd {int periodic_size; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  frame_index; } ;

/* Variables and functions */
 int ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 

__attribute__((used)) static int ehci_get_frame (struct usb_hcd *hcd)
{
	struct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	return (ehci_readl(ehci, &ehci->regs->frame_index) >> 3) %
		ehci->periodic_size;
}