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
typedef  int u64 ;
struct pci_iommu_arena {int dma_base; int size; } ;
struct pci_dev {struct pci_controller* sysdata; } ;
struct pci_controller {struct pci_iommu_arena* sg_pci; struct pci_iommu_arena* sg_isa; } ;

/* Variables and functions */
 int IDENT_ADDR ; 
 int MAX_DMA_ADDRESS ; 
 int PAGE_SHIFT ; 
 int __direct_map_base ; 
 int __direct_map_size ; 
 int max_low_pfn ; 
 struct pci_controller* pci_isa_hose ; 

int
pci_dma_supported(struct pci_dev *pdev, u64 mask)
{
	struct pci_controller *hose;
	struct pci_iommu_arena *arena;

	/* If there exists a direct map, and the mask fits either
	   the entire direct mapped space or the total system memory as
	   shifted by the map base */
	if (__direct_map_size != 0
	    && (__direct_map_base + __direct_map_size - 1 <= mask ||
		__direct_map_base + (max_low_pfn << PAGE_SHIFT) - 1 <= mask))
		return 1;

	/* Check that we have a scatter-gather arena that fits.  */
	hose = pdev ? pdev->sysdata : pci_isa_hose;
	arena = hose->sg_isa;
	if (arena && arena->dma_base + arena->size - 1 <= mask)
		return 1;
	arena = hose->sg_pci;
	if (arena && arena->dma_base + arena->size - 1 <= mask)
		return 1;

	/* As last resort try ZONE_DMA.  */
	if (!__direct_map_base && MAX_DMA_ADDRESS - IDENT_ADDR - 1 <= mask)
		return 1;

	return 0;
}