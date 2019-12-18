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
struct pci_dev {scalar_t__ vendor; scalar_t__ device; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_INTEL_IOAT_TBG0 ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_IOAT_TBG1 ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_IOAT_TBG2 ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_IOAT_TBG3 ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_IOAT_TBG4 ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_IOAT_TBG5 ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_IOAT_TBG6 ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_IOAT_TBG7 ; 
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int dca_provider_ioat_ver_3_0(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);

	return ((pdev->vendor == PCI_VENDOR_ID_INTEL) &&
		((pdev->device == PCI_DEVICE_ID_INTEL_IOAT_TBG0) ||
		(pdev->device == PCI_DEVICE_ID_INTEL_IOAT_TBG1) ||
		(pdev->device == PCI_DEVICE_ID_INTEL_IOAT_TBG2) ||
		(pdev->device == PCI_DEVICE_ID_INTEL_IOAT_TBG3) ||
		(pdev->device == PCI_DEVICE_ID_INTEL_IOAT_TBG4) ||
		(pdev->device == PCI_DEVICE_ID_INTEL_IOAT_TBG5) ||
		(pdev->device == PCI_DEVICE_ID_INTEL_IOAT_TBG6) ||
		(pdev->device == PCI_DEVICE_ID_INTEL_IOAT_TBG7)));
}