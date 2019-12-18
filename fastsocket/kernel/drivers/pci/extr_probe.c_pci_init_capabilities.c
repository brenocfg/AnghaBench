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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_allocate_cap_save_buffers (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_acs (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_ari (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iov_init (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_msi_init_pci_dev (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_pm_init (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_vpd_pci22_init (struct pci_dev*) ; 
 int /*<<< orphan*/  platform_pci_wakeup_init (struct pci_dev*) ; 

__attribute__((used)) static void pci_init_capabilities(struct pci_dev *dev)
{
	/* MSI/MSI-X list */
	pci_msi_init_pci_dev(dev);

	/* Buffers for saving PCIe and PCI-X capabilities */
	pci_allocate_cap_save_buffers(dev);

	/* Power Management */
	pci_pm_init(dev);
	platform_pci_wakeup_init(dev);

	/* Vital Product Data */
	pci_vpd_pci22_init(dev);

	/* Alternative Routing-ID Forwarding */
	pci_enable_ari(dev);

	/* Single Root I/O Virtualization */
	pci_iov_init(dev);

	/* Enable ACS P2P upstream forwarding */
	pci_enable_acs(dev);
}