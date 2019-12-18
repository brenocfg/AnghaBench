#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {struct iommu* iommu; } ;
struct TYPE_4__ {TYPE_1__ archdata; } ;
struct pci_dev {scalar_t__ vendor; scalar_t__ device; TYPE_2__ dev; } ;
struct iommu {int dma_addr_mask; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_AL_M5451 ; 
 scalar_t__ PCI_VENDOR_ID_AL ; 
 int /*<<< orphan*/  ali_sound_dma_hack (struct pci_dev*,int) ; 

int pci64_dma_supported(struct pci_dev *pdev, u64 device_mask)
{
	u64 dma_addr_mask;

	if (pdev == NULL) {
		dma_addr_mask = 0xffffffff;
	} else {
		struct iommu *iommu = pdev->dev.archdata.iommu;

		dma_addr_mask = iommu->dma_addr_mask;

		if (pdev->vendor == PCI_VENDOR_ID_AL &&
		    pdev->device == PCI_DEVICE_ID_AL_M5451 &&
		    device_mask == 0x7fffffff) {
			ali_sound_dma_hack(pdev,
					   (dma_addr_mask & 0x80000000) != 0);
			return 1;
		}
	}

	if (device_mask >= (1UL << 32UL))
		return 0;

	return (device_mask & dma_addr_mask) == dma_addr_mask;
}