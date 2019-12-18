#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int table_addr; int ready; int /*<<< orphan*/ * robj; } ;
struct TYPE_5__ {int gtt_start; int gtt_end; int gtt_size; } ;
struct TYPE_4__ {int addr; } ;
struct radeon_device {TYPE_3__ gart; TYPE_2__ mc; TYPE_1__ dummy_page; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BANK_SELECT_0 (int /*<<< orphan*/ ) ; 
 int BANK_SELECT_1 (int) ; 
 int /*<<< orphan*/  DRM_INFO (char*,unsigned int,unsigned long long) ; 
 int EFFECTIVE_L1_QUEUE_SIZE (int) ; 
 int EFFECTIVE_L1_TLB_SIZE (int) ; 
 int EFFECTIVE_L2_QUEUE_SIZE (int) ; 
 int EINVAL ; 
 int ENABLE_CONTEXT ; 
 int ENABLE_L1_FRAGMENT_PROCESSING ; 
 int ENABLE_L1_STRICT_ORDERING ; 
 int ENABLE_L1_TLB ; 
 int ENABLE_L2_CACHE ; 
 int ENABLE_L2_FRAGMENT_PROCESSING ; 
 int ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE ; 
 int ENABLE_SEMAPHORE_MODE ; 
 int ENABLE_WAIT_L2_QUERY ; 
 scalar_t__ MC_VM_L1_TLB_MCB_RD_GFX_CNTL ; 
 scalar_t__ MC_VM_L1_TLB_MCB_RD_HDP_CNTL ; 
 scalar_t__ MC_VM_L1_TLB_MCB_RD_PDMA_CNTL ; 
 scalar_t__ MC_VM_L1_TLB_MCB_RD_SEM_CNTL ; 
 scalar_t__ MC_VM_L1_TLB_MCB_RD_SYS_CNTL ; 
 scalar_t__ MC_VM_L1_TLB_MCB_WR_GFX_CNTL ; 
 scalar_t__ MC_VM_L1_TLB_MCB_WR_HDP_CNTL ; 
 scalar_t__ MC_VM_L1_TLB_MCB_WR_PDMA_CNTL ; 
 scalar_t__ MC_VM_L1_TLB_MCB_WR_SEM_CNTL ; 
 scalar_t__ MC_VM_L1_TLB_MCB_WR_SYS_CNTL ; 
 scalar_t__ MC_VM_L1_TLB_MCD_RD_A_CNTL ; 
 scalar_t__ MC_VM_L1_TLB_MCD_RD_B_CNTL ; 
 scalar_t__ MC_VM_L1_TLB_MCD_WR_A_CNTL ; 
 scalar_t__ MC_VM_L1_TLB_MCD_WR_B_CNTL ; 
 int PAGE_TABLE_DEPTH (int /*<<< orphan*/ ) ; 
 int RANGE_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int SYSTEM_ACCESS_MODE_NOT_IN_SYS ; 
 scalar_t__ VM_CONTEXT0_CNTL ; 
 scalar_t__ VM_CONTEXT0_PAGE_TABLE_BASE_ADDR ; 
 scalar_t__ VM_CONTEXT0_PAGE_TABLE_END_ADDR ; 
 scalar_t__ VM_CONTEXT0_PAGE_TABLE_START_ADDR ; 
 scalar_t__ VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR ; 
 scalar_t__ VM_L2_CNTL ; 
 scalar_t__ VM_L2_CNTL2 ; 
 scalar_t__ VM_L2_CNTL3 ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r600_pcie_gart_tlb_flush (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_gart_restore (struct radeon_device*) ; 
 int radeon_gart_table_vram_pin (struct radeon_device*) ; 

__attribute__((used)) static int r600_pcie_gart_enable(struct radeon_device *rdev)
{
	u32 tmp;
	int r, i;

	if (rdev->gart.robj == NULL) {
		dev_err(rdev->dev, "No VRAM object for PCIE GART.\n");
		return -EINVAL;
	}
	r = radeon_gart_table_vram_pin(rdev);
	if (r)
		return r;
	radeon_gart_restore(rdev);

	/* Setup L2 cache */
	WREG32(VM_L2_CNTL, ENABLE_L2_CACHE | ENABLE_L2_FRAGMENT_PROCESSING |
				ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE |
				EFFECTIVE_L2_QUEUE_SIZE(7));
	WREG32(VM_L2_CNTL2, 0);
	WREG32(VM_L2_CNTL3, BANK_SELECT_0(0) | BANK_SELECT_1(1));
	/* Setup TLB control */
	tmp = ENABLE_L1_TLB | ENABLE_L1_FRAGMENT_PROCESSING |
		SYSTEM_ACCESS_MODE_NOT_IN_SYS |
		EFFECTIVE_L1_TLB_SIZE(5) | EFFECTIVE_L1_QUEUE_SIZE(5) |
		ENABLE_WAIT_L2_QUERY;
	WREG32(MC_VM_L1_TLB_MCB_RD_SYS_CNTL, tmp);
	WREG32(MC_VM_L1_TLB_MCB_WR_SYS_CNTL, tmp);
	WREG32(MC_VM_L1_TLB_MCB_RD_HDP_CNTL, tmp | ENABLE_L1_STRICT_ORDERING);
	WREG32(MC_VM_L1_TLB_MCB_WR_HDP_CNTL, tmp);
	WREG32(MC_VM_L1_TLB_MCD_RD_A_CNTL, tmp);
	WREG32(MC_VM_L1_TLB_MCD_WR_A_CNTL, tmp);
	WREG32(MC_VM_L1_TLB_MCD_RD_B_CNTL, tmp);
	WREG32(MC_VM_L1_TLB_MCD_WR_B_CNTL, tmp);
	WREG32(MC_VM_L1_TLB_MCB_RD_GFX_CNTL, tmp);
	WREG32(MC_VM_L1_TLB_MCB_WR_GFX_CNTL, tmp);
	WREG32(MC_VM_L1_TLB_MCB_RD_PDMA_CNTL, tmp);
	WREG32(MC_VM_L1_TLB_MCB_WR_PDMA_CNTL, tmp);
	WREG32(MC_VM_L1_TLB_MCB_RD_SEM_CNTL, tmp | ENABLE_SEMAPHORE_MODE);
	WREG32(MC_VM_L1_TLB_MCB_WR_SEM_CNTL, tmp | ENABLE_SEMAPHORE_MODE);
	WREG32(VM_CONTEXT0_PAGE_TABLE_START_ADDR, rdev->mc.gtt_start >> 12);
	WREG32(VM_CONTEXT0_PAGE_TABLE_END_ADDR, rdev->mc.gtt_end >> 12);
	WREG32(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR, rdev->gart.table_addr >> 12);
	WREG32(VM_CONTEXT0_CNTL, ENABLE_CONTEXT | PAGE_TABLE_DEPTH(0) |
				RANGE_PROTECTION_FAULT_ENABLE_DEFAULT);
	WREG32(VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR,
			(u32)(rdev->dummy_page.addr >> 12));
	for (i = 1; i < 7; i++)
		WREG32(VM_CONTEXT0_CNTL + (i * 4), 0);

	r600_pcie_gart_tlb_flush(rdev);
	DRM_INFO("PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (unsigned)(rdev->mc.gtt_size >> 20),
		 (unsigned long long)rdev->gart.table_addr);
	rdev->gart.ready = true;
	return 0;
}