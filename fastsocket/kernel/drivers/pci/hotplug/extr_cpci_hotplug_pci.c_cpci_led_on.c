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
typedef  int u16 ;
struct slot {int /*<<< orphan*/  hotplug_slot; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int ENODEV ; 
 int HS_CSR_LOO ; 
 int /*<<< orphan*/  PCI_CAP_ID_CHSWP ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hotplug_slot_name (int /*<<< orphan*/ ) ; 
 int pci_bus_find_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_bus_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ pci_bus_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int cpci_led_on(struct slot* slot)
{
	int hs_cap;
	u16 hs_csr;

	hs_cap = pci_bus_find_capability(slot->bus,
					 slot->devfn,
					 PCI_CAP_ID_CHSWP);
	if (!hs_cap)
		return -ENODEV;
	if (pci_bus_read_config_word(slot->bus,
				     slot->devfn,
				     hs_cap + 2,
				     &hs_csr))
		return -ENODEV;
	if ((hs_csr & HS_CSR_LOO) != HS_CSR_LOO) {
		hs_csr |= HS_CSR_LOO;
		if (pci_bus_write_config_word(slot->bus,
					      slot->devfn,
					      hs_cap + 2,
					      hs_csr)) {
			err("Could not set LOO for slot %s",
			    hotplug_slot_name(slot->hotplug_slot));
			return -ENODEV;
		}
	}
	return 0;
}