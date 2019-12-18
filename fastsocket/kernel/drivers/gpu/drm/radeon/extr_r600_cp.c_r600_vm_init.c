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
typedef  int u32 ;
struct drm_device {TYPE_2__* dev_private; } ;
struct TYPE_3__ {int bus_addr; } ;
struct TYPE_4__ {int gart_vm_start; int gart_size; TYPE_1__ gart_info; } ;
typedef  TYPE_2__ drm_radeon_private_t ;

/* Variables and functions */
 int R600_MCD_EFFECTIVE_L1_QUEUE_SIZE (int) ; 
 int R600_MCD_EFFECTIVE_L1_TLB_SIZE (int) ; 
 int R600_MCD_L1_FRAG_PROC ; 
 int R600_MCD_L1_STRICT_ORDERING ; 
 int R600_MCD_L1_TLB ; 
 scalar_t__ R600_MCD_RD_A_CNTL ; 
 scalar_t__ R600_MCD_RD_B_CNTL ; 
 scalar_t__ R600_MCD_RD_GFX_CNTL ; 
 scalar_t__ R600_MCD_RD_HDP_CNTL ; 
 scalar_t__ R600_MCD_RD_PDMA_CNTL ; 
 scalar_t__ R600_MCD_RD_SEM_CNTL ; 
 scalar_t__ R600_MCD_RD_SYS_CNTL ; 
 int R600_MCD_SEMAPHORE_MODE ; 
 int R600_MCD_SYSTEM_ACCESS_MODE_IN_SYS ; 
 int R600_MCD_SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU ; 
 int R600_MCD_WAIT_L2_QUERY ; 
 scalar_t__ R600_MCD_WR_A_CNTL ; 
 scalar_t__ R600_MCD_WR_B_CNTL ; 
 scalar_t__ R600_MCD_WR_GFX_CNTL ; 
 scalar_t__ R600_MCD_WR_HDP_CNTL ; 
 scalar_t__ R600_MCD_WR_PDMA_CNTL ; 
 scalar_t__ R600_MCD_WR_SEM_CNTL ; 
 scalar_t__ R600_MCD_WR_SYS_CNTL ; 
 scalar_t__ R600_MC_VM_SYSTEM_APERTURE_DEFAULT_ADDR ; 
 scalar_t__ R600_MC_VM_SYSTEM_APERTURE_HIGH_ADDR ; 
 scalar_t__ R600_MC_VM_SYSTEM_APERTURE_LOW_ADDR ; 
 scalar_t__ R600_VM_CONTEXT0_CNTL ; 
 scalar_t__ R600_VM_CONTEXT0_PAGE_TABLE_BASE_ADDR ; 
 scalar_t__ R600_VM_CONTEXT0_PAGE_TABLE_END_ADDR ; 
 scalar_t__ R600_VM_CONTEXT0_PAGE_TABLE_START_ADDR ; 
 int R600_VM_ENABLE_CONTEXT ; 
 int R600_VM_ENABLE_PTE_CACHE_LRU_W ; 
 int R600_VM_L2_CACHE_EN ; 
 scalar_t__ R600_VM_L2_CNTL ; 
 scalar_t__ R600_VM_L2_CNTL2 ; 
 scalar_t__ R600_VM_L2_CNTL3 ; 
 int R600_VM_L2_CNTL3_BANK_SELECT_0 (int /*<<< orphan*/ ) ; 
 int R600_VM_L2_CNTL3_BANK_SELECT_1 (int) ; 
 int R600_VM_L2_CNTL3_CACHE_UPDATE_MODE (int) ; 
 int R600_VM_L2_CNTL_QUEUE_SIZE (int) ; 
 int R600_VM_L2_FRAG_PROC ; 
 int R600_VM_PAGE_TABLE_DEPTH_FLAT ; 
 int /*<<< orphan*/  RADEON_WRITE (scalar_t__,int) ; 
 int /*<<< orphan*/  r600_vm_flush_gart_range (struct drm_device*) ; 

__attribute__((used)) static void r600_vm_init(struct drm_device *dev)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	/* initialise the VM to use the page table we constructed up there */
	u32 vm_c0, i;
	u32 mc_rd_a;
	u32 vm_l2_cntl, vm_l2_cntl3;
	/* okay set up the PCIE aperture type thingo */
	RADEON_WRITE(R600_MC_VM_SYSTEM_APERTURE_LOW_ADDR, dev_priv->gart_vm_start >> 12);
	RADEON_WRITE(R600_MC_VM_SYSTEM_APERTURE_HIGH_ADDR, (dev_priv->gart_vm_start + dev_priv->gart_size - 1) >> 12);
	RADEON_WRITE(R600_MC_VM_SYSTEM_APERTURE_DEFAULT_ADDR, 0);

	/* setup MC RD a */
	mc_rd_a = R600_MCD_L1_TLB | R600_MCD_L1_FRAG_PROC | R600_MCD_SYSTEM_ACCESS_MODE_IN_SYS |
		R600_MCD_SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU | R600_MCD_EFFECTIVE_L1_TLB_SIZE(5) |
		R600_MCD_EFFECTIVE_L1_QUEUE_SIZE(5) | R600_MCD_WAIT_L2_QUERY;

	RADEON_WRITE(R600_MCD_RD_A_CNTL, mc_rd_a);
	RADEON_WRITE(R600_MCD_RD_B_CNTL, mc_rd_a);

	RADEON_WRITE(R600_MCD_WR_A_CNTL, mc_rd_a);
	RADEON_WRITE(R600_MCD_WR_B_CNTL, mc_rd_a);

	RADEON_WRITE(R600_MCD_RD_GFX_CNTL, mc_rd_a);
	RADEON_WRITE(R600_MCD_WR_GFX_CNTL, mc_rd_a);

	RADEON_WRITE(R600_MCD_RD_SYS_CNTL, mc_rd_a);
	RADEON_WRITE(R600_MCD_WR_SYS_CNTL, mc_rd_a);

	RADEON_WRITE(R600_MCD_RD_HDP_CNTL, mc_rd_a | R600_MCD_L1_STRICT_ORDERING);
	RADEON_WRITE(R600_MCD_WR_HDP_CNTL, mc_rd_a /*| R600_MCD_L1_STRICT_ORDERING*/);

	RADEON_WRITE(R600_MCD_RD_PDMA_CNTL, mc_rd_a);
	RADEON_WRITE(R600_MCD_WR_PDMA_CNTL, mc_rd_a);

	RADEON_WRITE(R600_MCD_RD_SEM_CNTL, mc_rd_a | R600_MCD_SEMAPHORE_MODE);
	RADEON_WRITE(R600_MCD_WR_SEM_CNTL, mc_rd_a);

	vm_l2_cntl = R600_VM_L2_CACHE_EN | R600_VM_L2_FRAG_PROC | R600_VM_ENABLE_PTE_CACHE_LRU_W;
	vm_l2_cntl |= R600_VM_L2_CNTL_QUEUE_SIZE(7);
	RADEON_WRITE(R600_VM_L2_CNTL, vm_l2_cntl);

	RADEON_WRITE(R600_VM_L2_CNTL2, 0);
	vm_l2_cntl3 = (R600_VM_L2_CNTL3_BANK_SELECT_0(0) |
		       R600_VM_L2_CNTL3_BANK_SELECT_1(1) |
		       R600_VM_L2_CNTL3_CACHE_UPDATE_MODE(2));
	RADEON_WRITE(R600_VM_L2_CNTL3, vm_l2_cntl3);

	vm_c0 = R600_VM_ENABLE_CONTEXT | R600_VM_PAGE_TABLE_DEPTH_FLAT;

	RADEON_WRITE(R600_VM_CONTEXT0_CNTL, vm_c0);

	vm_c0 &= ~R600_VM_ENABLE_CONTEXT;

	/* disable all other contexts */
	for (i = 1; i < 8; i++)
		RADEON_WRITE(R600_VM_CONTEXT0_CNTL + (i * 4), vm_c0);

	RADEON_WRITE(R600_VM_CONTEXT0_PAGE_TABLE_BASE_ADDR, dev_priv->gart_info.bus_addr >> 12);
	RADEON_WRITE(R600_VM_CONTEXT0_PAGE_TABLE_START_ADDR, dev_priv->gart_vm_start >> 12);
	RADEON_WRITE(R600_VM_CONTEXT0_PAGE_TABLE_END_ADDR, (dev_priv->gart_vm_start + dev_priv->gart_size - 1) >> 12);

	r600_vm_flush_gart_range(dev);
}