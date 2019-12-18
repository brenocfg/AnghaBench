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
struct pci_dn {int eeh_freeze_count; scalar_t__ eeh_pe_config_addr; struct device_node* node; } ;
struct pci_bus {int dummy; } ;
struct device_node {struct device_node* sibling; struct device_node* child; struct device_node* parent; } ;

/* Variables and functions */
 struct pci_dn* PCI_DN (struct device_node*) ; 
 int /*<<< orphan*/  eeh_restore_bars (struct pci_dn*) ; 
 int /*<<< orphan*/  pcibios_add_pci_devices (struct pci_bus*) ; 
 int /*<<< orphan*/  pcibios_find_pci_bus (struct device_node*) ; 
 int /*<<< orphan*/  pcibios_remove_pci_devices (struct pci_bus*) ; 
 int /*<<< orphan*/  rtas_configure_bridge (struct pci_dn*) ; 
 int rtas_set_slot_reset (struct pci_dn*) ; 
 int /*<<< orphan*/  ssleep (int) ; 

__attribute__((used)) static int eeh_reset_device (struct pci_dn *pe_dn, struct pci_bus *bus)
{
	struct device_node *dn;
	int cnt, rc;

	/* pcibios will clear the counter; save the value */
	cnt = pe_dn->eeh_freeze_count;

	if (bus)
		pcibios_remove_pci_devices(bus);

	/* Reset the pci controller. (Asserts RST#; resets config space).
	 * Reconfigure bridges and devices. Don't try to bring the system
	 * up if the reset failed for some reason. */
	rc = rtas_set_slot_reset(pe_dn);
	if (rc)
		return rc;

	/* Walk over all functions on this device.  */
	dn = pe_dn->node;
	if (!pcibios_find_pci_bus(dn) && PCI_DN(dn->parent))
		dn = dn->parent->child;

	while (dn) {
		struct pci_dn *ppe = PCI_DN(dn);
		/* On Power4, always true because eeh_pe_config_addr=0 */
		if (pe_dn->eeh_pe_config_addr == ppe->eeh_pe_config_addr) {
			rtas_configure_bridge(ppe);
			eeh_restore_bars(ppe);
 		}
		dn = dn->sibling;
	}

	/* Give the system 5 seconds to finish running the user-space
	 * hotplug shutdown scripts, e.g. ifdown for ethernet.  Yes, 
	 * this is a hack, but if we don't do this, and try to bring 
	 * the device up before the scripts have taken it down, 
	 * potentially weird things happen.
	 */
	if (bus) {
		ssleep (5);
		pcibios_add_pci_devices(bus);
	}
	pe_dn->eeh_freeze_count = cnt;

	return 0;
}