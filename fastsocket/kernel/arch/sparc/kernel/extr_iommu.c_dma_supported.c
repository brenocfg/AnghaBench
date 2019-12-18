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
typedef  unsigned long u64 ;
struct iommu {unsigned long dma_addr_mask; } ;
struct TYPE_2__ {struct iommu* iommu; } ;
struct device {int /*<<< orphan*/ * bus; TYPE_1__ archdata; } ;

/* Variables and functions */
 int pci64_dma_supported (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pci_bus_type ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 

int dma_supported(struct device *dev, u64 device_mask)
{
	struct iommu *iommu = dev->archdata.iommu;
	u64 dma_addr_mask = iommu->dma_addr_mask;

	if (device_mask >= (1UL << 32UL))
		return 0;

	if ((device_mask & dma_addr_mask) == dma_addr_mask)
		return 1;

#ifdef CONFIG_PCI
	if (dev->bus == &pci_bus_type)
		return pci64_dma_supported(to_pci_dev(dev), device_mask);
#endif

	return 0;
}