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
typedef  scalar_t__ u64 ;
struct pci_dev {unsigned long dma_mask; } ;

/* Variables and functions */
 int SN_DMA_MSI ; 
 scalar_t__ tioca_dma_d48 (struct pci_dev*,scalar_t__) ; 
 scalar_t__ tioca_dma_d64 (scalar_t__) ; 
 scalar_t__ tioca_dma_mapped (struct pci_dev*,scalar_t__,size_t) ; 

__attribute__((used)) static u64
tioca_dma_map(struct pci_dev *pdev, u64 paddr, size_t byte_count, int dma_flags)
{
	u64 mapaddr;

	/*
	 * Not supported for now ...
	 */
	if (dma_flags & SN_DMA_MSI)
		return 0;

	/*
	 * If card is 64 or 48 bit addressable, use a direct mapping.  32
	 * bit direct is so restrictive w.r.t. where the memory resides that
	 * we don't use it even though CA has some support.
	 */

	if (pdev->dma_mask == ~0UL)
		mapaddr = tioca_dma_d64(paddr);
	else if (pdev->dma_mask == 0xffffffffffffUL)
		mapaddr = tioca_dma_d48(pdev, paddr);
	else
		mapaddr = 0;

	/* Last resort ... use PCI portion of CA GART */

	if (mapaddr == 0)
		mapaddr = tioca_dma_mapped(pdev, paddr, byte_count);

	return mapaddr;
}