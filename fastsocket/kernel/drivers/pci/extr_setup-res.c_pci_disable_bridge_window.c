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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_MEMORY_BASE ; 
 int /*<<< orphan*/  PCI_PREF_BASE_UPPER32 ; 
 int /*<<< orphan*/  PCI_PREF_LIMIT_UPPER32 ; 
 int /*<<< orphan*/  PCI_PREF_MEMORY_BASE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

void pci_disable_bridge_window(struct pci_dev *dev)
{
	dev_info(&dev->dev, "disabling bridge mem windows\n");

	/* MMIO Base/Limit */
	pci_write_config_dword(dev, PCI_MEMORY_BASE, 0x0000fff0);

	/* Prefetchable MMIO Base/Limit */
	pci_write_config_dword(dev, PCI_PREF_LIMIT_UPPER32, 0);
	pci_write_config_dword(dev, PCI_PREF_MEMORY_BASE, 0x0000fff0);
	pci_write_config_dword(dev, PCI_PREF_BASE_UPPER32, 0xffffffff);
}