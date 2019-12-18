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
struct radeon_device {int flags; scalar_t__ family; TYPE_3__ gart; TYPE_2__ mc; TYPE_1__ dummy_page; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BANK_SELECT (int /*<<< orphan*/ ) ; 
 int CACHE_UPDATE_MODE (int) ; 
 scalar_t__ CHIP_BARTS ; 
 scalar_t__ CHIP_CYPRESS ; 
 scalar_t__ CHIP_HEMLOCK ; 
 scalar_t__ CHIP_JUNIPER ; 
 int /*<<< orphan*/  DRM_INFO (char*,unsigned int,unsigned long long) ; 
 int EFFECTIVE_L1_QUEUE_SIZE (int) ; 
 int EFFECTIVE_L1_TLB_SIZE (int) ; 
 int EFFECTIVE_L2_QUEUE_SIZE (int) ; 
 int EINVAL ; 
 int ENABLE_CONTEXT ; 
 int ENABLE_L1_FRAGMENT_PROCESSING ; 
 int ENABLE_L1_TLB ; 
 int ENABLE_L2_CACHE ; 
 int ENABLE_L2_FRAGMENT_PROCESSING ; 
 int ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE ; 
 int /*<<< orphan*/  FUS_MC_VM_MD_L1_TLB0_CNTL ; 
 int /*<<< orphan*/  FUS_MC_VM_MD_L1_TLB1_CNTL ; 
 int /*<<< orphan*/  FUS_MC_VM_MD_L1_TLB2_CNTL ; 
 int /*<<< orphan*/  MC_VM_MB_L1_TLB0_CNTL ; 
 int /*<<< orphan*/  MC_VM_MB_L1_TLB1_CNTL ; 
 int /*<<< orphan*/  MC_VM_MB_L1_TLB2_CNTL ; 
 int /*<<< orphan*/  MC_VM_MB_L1_TLB3_CNTL ; 
 int /*<<< orphan*/  MC_VM_MD_L1_TLB0_CNTL ; 
 int /*<<< orphan*/  MC_VM_MD_L1_TLB1_CNTL ; 
 int /*<<< orphan*/  MC_VM_MD_L1_TLB2_CNTL ; 
 int /*<<< orphan*/  MC_VM_MD_L1_TLB3_CNTL ; 
 int PAGE_TABLE_DEPTH (int /*<<< orphan*/ ) ; 
 int RADEON_IS_IGP ; 
 int RANGE_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int SYSTEM_ACCESS_MODE_NOT_IN_SYS ; 
 int SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU ; 
 int /*<<< orphan*/  VM_CONTEXT0_CNTL ; 
 int /*<<< orphan*/  VM_CONTEXT0_PAGE_TABLE_BASE_ADDR ; 
 int /*<<< orphan*/  VM_CONTEXT0_PAGE_TABLE_END_ADDR ; 
 int /*<<< orphan*/  VM_CONTEXT0_PAGE_TABLE_START_ADDR ; 
 int /*<<< orphan*/  VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR ; 
 int /*<<< orphan*/  VM_CONTEXT1_CNTL ; 
 int /*<<< orphan*/  VM_L2_CNTL ; 
 int /*<<< orphan*/  VM_L2_CNTL2 ; 
 int /*<<< orphan*/  VM_L2_CNTL3 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evergreen_pcie_gart_tlb_flush (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_gart_restore (struct radeon_device*) ; 
 int radeon_gart_table_vram_pin (struct radeon_device*) ; 

__attribute__((used)) static int evergreen_pcie_gart_enable(struct radeon_device *rdev)
{
	u32 tmp;
	int r;

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
	WREG32(VM_L2_CNTL3, BANK_SELECT(0) | CACHE_UPDATE_MODE(2));
	/* Setup TLB control */
	tmp = ENABLE_L1_TLB | ENABLE_L1_FRAGMENT_PROCESSING |
		SYSTEM_ACCESS_MODE_NOT_IN_SYS |
		SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU |
		EFFECTIVE_L1_TLB_SIZE(5) | EFFECTIVE_L1_QUEUE_SIZE(5);
	if (rdev->flags & RADEON_IS_IGP) {
		WREG32(FUS_MC_VM_MD_L1_TLB0_CNTL, tmp);
		WREG32(FUS_MC_VM_MD_L1_TLB1_CNTL, tmp);
		WREG32(FUS_MC_VM_MD_L1_TLB2_CNTL, tmp);
	} else {
		WREG32(MC_VM_MD_L1_TLB0_CNTL, tmp);
		WREG32(MC_VM_MD_L1_TLB1_CNTL, tmp);
		WREG32(MC_VM_MD_L1_TLB2_CNTL, tmp);
		if ((rdev->family == CHIP_JUNIPER) ||
		    (rdev->family == CHIP_CYPRESS) ||
		    (rdev->family == CHIP_HEMLOCK) ||
		    (rdev->family == CHIP_BARTS))
			WREG32(MC_VM_MD_L1_TLB3_CNTL, tmp);
	}
	WREG32(MC_VM_MB_L1_TLB0_CNTL, tmp);
	WREG32(MC_VM_MB_L1_TLB1_CNTL, tmp);
	WREG32(MC_VM_MB_L1_TLB2_CNTL, tmp);
	WREG32(MC_VM_MB_L1_TLB3_CNTL, tmp);
	WREG32(VM_CONTEXT0_PAGE_TABLE_START_ADDR, rdev->mc.gtt_start >> 12);
	WREG32(VM_CONTEXT0_PAGE_TABLE_END_ADDR, rdev->mc.gtt_end >> 12);
	WREG32(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR, rdev->gart.table_addr >> 12);
	WREG32(VM_CONTEXT0_CNTL, ENABLE_CONTEXT | PAGE_TABLE_DEPTH(0) |
				RANGE_PROTECTION_FAULT_ENABLE_DEFAULT);
	WREG32(VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR,
			(u32)(rdev->dummy_page.addr >> 12));
	WREG32(VM_CONTEXT1_CNTL, 0);

	evergreen_pcie_gart_tlb_flush(rdev);
	DRM_INFO("PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (unsigned)(rdev->mc.gtt_size >> 20),
		 (unsigned long long)rdev->gart.table_addr);
	rdev->gart.ready = true;
	return 0;
}