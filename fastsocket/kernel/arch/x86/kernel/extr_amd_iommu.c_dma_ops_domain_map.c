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
struct dma_ops_domain {unsigned long aperture_size; } ;
struct amd_iommu {int dummy; } ;
typedef  int phys_addr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int DMA_BIDIRECTIONAL ; 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int IOMMU_PTE_FC ; 
 int IOMMU_PTE_IR ; 
 int IOMMU_PTE_IW ; 
 int IOMMU_PTE_P ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bad_dma_address ; 
 int* dma_ops_get_pte (struct dma_ops_domain*,unsigned long) ; 

__attribute__((used)) static dma_addr_t dma_ops_domain_map(struct amd_iommu *iommu,
				     struct dma_ops_domain *dom,
				     unsigned long address,
				     phys_addr_t paddr,
				     int direction)
{
	u64 *pte, __pte;

	WARN_ON(address > dom->aperture_size);

	paddr &= PAGE_MASK;

	pte  = dma_ops_get_pte(dom, address);
	if (!pte)
		return bad_dma_address;

	__pte = paddr | IOMMU_PTE_P | IOMMU_PTE_FC;

	if (direction == DMA_TO_DEVICE)
		__pte |= IOMMU_PTE_IR;
	else if (direction == DMA_FROM_DEVICE)
		__pte |= IOMMU_PTE_IW;
	else if (direction == DMA_BIDIRECTIONAL)
		__pte |= IOMMU_PTE_IR | IOMMU_PTE_IW;

	WARN_ON(*pte);

	*pte = __pte;

	return (dma_addr_t)address;
}