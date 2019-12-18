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
struct pci_dn {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEH_MODE_ISOLATED ; 
 int /*<<< orphan*/  PCI_BUS_RST_HOLD_TIME_MSEC ; 
 int /*<<< orphan*/  PCI_BUS_SETTLE_TIME_MSEC ; 
 int /*<<< orphan*/  eeh_clear_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeh_set_pe_freset (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtas_pci_slot_reset (struct pci_dn*,int) ; 

__attribute__((used)) static void __rtas_set_slot_reset(struct pci_dn *pdn)
{
	unsigned int freset = 0;

	/* Determine type of EEH reset required for
	 * Partitionable Endpoint, a hot-reset (1)
	 * or a fundamental reset (3).
	 * A fundamental reset required by any device under
	 * Partitionable Endpoint trumps hot-reset.
	 */
	eeh_set_pe_freset(pdn->node, &freset);

	if (freset)
		rtas_pci_slot_reset(pdn, 3);
	else
		rtas_pci_slot_reset(pdn, 1);

	/* The PCI bus requires that the reset be held high for at least
	 * a 100 milliseconds. We wait a bit longer 'just in case'.  */

#define PCI_BUS_RST_HOLD_TIME_MSEC 250
	msleep (PCI_BUS_RST_HOLD_TIME_MSEC);
	
	/* We might get hit with another EEH freeze as soon as the 
	 * pci slot reset line is dropped. Make sure we don't miss
	 * these, and clear the flag now. */
	eeh_clear_slot (pdn->node, EEH_MODE_ISOLATED);

	rtas_pci_slot_reset (pdn, 0);

	/* After a PCI slot has been reset, the PCI Express spec requires
	 * a 1.5 second idle time for the bus to stabilize, before starting
	 * up traffic. */
#define PCI_BUS_SETTLE_TIME_MSEC 1800
	msleep (PCI_BUS_SETTLE_TIME_MSEC);
}