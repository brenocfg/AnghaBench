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
typedef  int u8 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int pcie_get_mps (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_get_readrq (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_write_mps (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pcie_write_mrrs (struct pci_dev*) ; 
 int rh_get_mpss (struct pci_dev*) ; 

__attribute__((used)) static int pcie_bus_configure_set(struct pci_dev *dev, void *data)
{
	int mps, orig_mps;

	if (!pci_is_pcie(dev))
		return 0;

	mps = 128 << *(u8 *)data;
	orig_mps = pcie_get_mps(dev);

	pcie_write_mps(dev, mps);
	pcie_write_mrrs(dev);

	dev_info(&dev->dev, "PCI-E Max Payload Size set to %4d/%4d (was %4d), "
		 "Max Read Rq %4d\n", pcie_get_mps(dev),
		 128 << rh_get_mpss(dev), orig_mps, pcie_get_readrq(dev));

	return 0;
}