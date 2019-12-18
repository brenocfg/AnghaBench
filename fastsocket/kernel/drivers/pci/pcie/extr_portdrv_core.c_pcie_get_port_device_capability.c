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
typedef  int u32 ;
struct pci_dev_rh1 {int __pcie_osc_capabilities_valid; int pcie_osc_capabilities; } ;
struct pci_dev {struct pci_dev_rh1* rh_reserved1; } ;

/* Variables and functions */
 int PCIE_PORT_SERVICE_AER ; 
 int PCIE_PORT_SERVICE_HP ; 
 int PCIE_PORT_SERVICE_PME ; 
 int PCIE_PORT_SERVICE_VC ; 
 int PCI_EXP_FLAGS_SLOT ; 
 int /*<<< orphan*/  PCI_EXP_SLTCAP ; 
 int PCI_EXP_SLTCAP_HPC ; 
 scalar_t__ PCI_EXP_TYPE_ROOT_PORT ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ERR ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_VC ; 
 scalar_t__ pci_aer_available () ; 
 scalar_t__ pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_capability_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int pcie_caps_reg (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_no_aspm () ; 
 int pcie_port_platform_notify (struct pci_dev*,int*) ; 
 scalar_t__ pcie_ports_auto ; 

int pcie_get_port_device_capability(struct pci_dev *dev)
{
	int services = 0;
	u32 reg32;
	int cap_mask = 0;
	int err;
	struct pci_dev_rh1 *rh1_pci = dev->rh_reserved1;

	if (rh1_pci->__pcie_osc_capabilities_valid)
		return rh1_pci->pcie_osc_capabilities;

	err = pcie_port_platform_notify(dev, &cap_mask);
	if (pcie_ports_auto) {
		if (err) {
			pcie_no_aspm();
			return 0;
		}
	} else {
		cap_mask = PCIE_PORT_SERVICE_PME | PCIE_PORT_SERVICE_HP
				| PCIE_PORT_SERVICE_VC;
		if (pci_aer_available())
			cap_mask |= PCIE_PORT_SERVICE_AER;
	}

	/* Hot-Plug Capable */
	if ((cap_mask & PCIE_PORT_SERVICE_HP) &&
	    pcie_caps_reg(dev) & PCI_EXP_FLAGS_SLOT) {
		pcie_capability_read_dword(dev, PCI_EXP_SLTCAP, &reg32);
		if (reg32 & PCI_EXP_SLTCAP_HPC)
			services |= PCIE_PORT_SERVICE_HP;
	}
	/* AER capable */
	if ((cap_mask & PCIE_PORT_SERVICE_AER)
	    && (pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ERR)))
		services |= PCIE_PORT_SERVICE_AER;
	/* VC support */
	if (pci_find_ext_capability(dev, PCI_EXT_CAP_ID_VC))
		services |= PCIE_PORT_SERVICE_VC;
	if ((cap_mask & PCIE_PORT_SERVICE_PME)
	    && pci_pcie_type(dev) == PCI_EXP_TYPE_ROOT_PORT)
		services |= PCIE_PORT_SERVICE_PME;

	rh1_pci->pcie_osc_capabilities = services;
	rh1_pci->__pcie_osc_capabilities_valid = 1;

	return services;
}