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
typedef  scalar_t__ u8 ;
struct pci_bus {int /*<<< orphan*/  self; } ;

/* Variables and functions */
 scalar_t__ PCIE_BUS_PEER2PEER ; 
 scalar_t__ PCIE_BUS_SAFE ; 
 scalar_t__ PCIE_BUS_TUNE_OFF ; 
 int /*<<< orphan*/  pci_is_pcie (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_walk_bus (struct pci_bus*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,scalar_t__*),scalar_t__*) ; 
 scalar_t__ pcie_bus_config ; 
 int /*<<< orphan*/  pcie_bus_configure_set (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pcie_find_smpss (int /*<<< orphan*/ ,scalar_t__*) ; 

void pcie_bus_configure_settings(struct pci_bus *bus, u8 mpss)
{
	u8 smpss;

	if (!pci_is_pcie(bus->self))
		return;

	if (pcie_bus_config == PCIE_BUS_TUNE_OFF)
		return;

	/* FIXME - Peer to peer DMA is possible, though the endpoint would need
	 * to be aware to the MPS of the destination.  To work around this,
	 * simply force the MPS of the entire system to the smallest possible.
	 */
	if (pcie_bus_config == PCIE_BUS_PEER2PEER)
		smpss = 0;

	if (pcie_bus_config == PCIE_BUS_SAFE) {
		smpss = mpss;

		pcie_find_smpss(bus->self, &smpss);
		pci_walk_bus(bus, pcie_find_smpss, &smpss);
	}

	pcie_bus_configure_set(bus->self, &smpss);
	pci_walk_bus(bus, pcie_bus_configure_set, &smpss);
}