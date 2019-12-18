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
struct uhci_hcd {int rh_numports; scalar_t__ io_addr; } ;
struct TYPE_2__ {int vendor; } ;

/* Variables and functions */
#define  PCI_VENDOR_ID_GENESYS 129 
#define  PCI_VENDOR_ID_INTEL 128 
 scalar_t__ USBPORTSC1 ; 
 int USBPORTSC_OC ; 
 scalar_t__ ignore_oc ; 
 int inw (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uhci_dev (struct uhci_hcd*) ; 

__attribute__((used)) static int resume_detect_interrupts_are_broken(struct uhci_hcd *uhci)
{
	int port;

	/* If we have to ignore overcurrent events then almost by definition
	 * we can't depend on resume-detect interrupts. */
	if (ignore_oc)
		return 1;

	switch (to_pci_dev(uhci_dev(uhci))->vendor) {
	    default:
		break;

	    case PCI_VENDOR_ID_GENESYS:
		/* Genesys Logic's GL880S controllers don't generate
		 * resume-detect interrupts.
		 */
		return 1;

	    case PCI_VENDOR_ID_INTEL:
		/* Some of Intel's USB controllers have a bug that causes
		 * resume-detect interrupts if any port has an over-current
		 * condition.  To make matters worse, some motherboards
		 * hardwire unused USB ports' over-current inputs active!
		 * To prevent problems, we will not enable resume-detect
		 * interrupts if any ports are OC.
		 */
		for (port = 0; port < uhci->rh_numports; ++port) {
			if (inw(uhci->io_addr + USBPORTSC1 + port * 2) &
					USBPORTSC_OC)
				return 1;
		}
		break;
	}
	return 0;
}