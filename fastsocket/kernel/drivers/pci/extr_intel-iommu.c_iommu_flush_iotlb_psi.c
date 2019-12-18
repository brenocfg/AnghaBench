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
typedef  int uint64_t ;
typedef  size_t u16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_iotlb ) (struct intel_iommu*,size_t,int,unsigned int,int /*<<< orphan*/ ) ;} ;
struct intel_iommu {int /*<<< orphan*/ * domains; int /*<<< orphan*/  cap; TYPE_1__ flush; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_TLB_DSI_FLUSH ; 
 int /*<<< orphan*/  DMA_TLB_PSI_FLUSH ; 
 int VTD_PAGE_SHIFT ; 
 int /*<<< orphan*/  __roundup_pow_of_two (unsigned int) ; 
 int /*<<< orphan*/  cap_caching_mode (int /*<<< orphan*/ ) ; 
 unsigned int cap_max_amask_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_pgsel_inv (int /*<<< orphan*/ ) ; 
 unsigned int ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_flush_dev_iotlb (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct intel_iommu*,size_t,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct intel_iommu*,size_t,int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iommu_flush_iotlb_psi(struct intel_iommu *iommu, u16 did,
				  unsigned long pfn, unsigned int pages)
{
	unsigned int mask = ilog2(__roundup_pow_of_two(pages));
	uint64_t addr = (uint64_t)pfn << VTD_PAGE_SHIFT;

	BUG_ON(pages == 0);

	/*
	 * Fallback to domain selective flush if no PSI support or the size is
	 * too big.
	 * PSI requires page size to be 2 ^ x, and the base address is naturally
	 * aligned to the size
	 */
	if (!cap_pgsel_inv(iommu->cap) || mask > cap_max_amask_val(iommu->cap))
		iommu->flush.flush_iotlb(iommu, did, 0, 0,
						DMA_TLB_DSI_FLUSH);
	else
		iommu->flush.flush_iotlb(iommu, did, addr, mask,
						DMA_TLB_PSI_FLUSH);

	/*
	 * In caching mode, domain ID 0 is reserved for non-present to present
	 * mapping flush. Device IOTLB doesn't need to be flushed in this case.
	 */
	if (!cap_caching_mode(iommu->cap) || did)
		iommu_flush_dev_iotlb(iommu->domains[did], addr, mask);
}