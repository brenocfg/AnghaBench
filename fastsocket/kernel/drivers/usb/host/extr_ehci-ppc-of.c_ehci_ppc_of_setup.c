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
struct usb_hcd {int dummy; } ;
struct ehci_hcd {int sbrn; } ;

/* Variables and functions */
 int ehci_halt (struct ehci_hcd*) ; 
 int ehci_init (struct usb_hcd*) ; 
 int ehci_reset (struct ehci_hcd*) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 

__attribute__((used)) static int ehci_ppc_of_setup(struct usb_hcd *hcd)
{
	struct ehci_hcd	*ehci = hcd_to_ehci(hcd);
	int		retval;

	retval = ehci_halt(ehci);
	if (retval)
		return retval;

	retval = ehci_init(hcd);
	if (retval)
		return retval;

	ehci->sbrn = 0x20;
	return ehci_reset(ehci);
}