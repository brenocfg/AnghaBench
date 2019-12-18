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
typedef  int u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int CB_BUSY ; 
 int CF_RQ_PENDING ; 
 int CP_BUSY ; 
 int CP_COHERENCY_BUSY ; 
 int DB_BUSY ; 
 int DMA_BUSY ; 
 int DMA_IDLE ; 
 int /*<<< orphan*/  DMA_STATUS_REG ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int GRBM_EE_BUSY ; 
 int GRBM_RQ_PENDING ; 
 int /*<<< orphan*/  GRBM_STATUS ; 
 int IH_BUSY ; 
 int L2_BUSY ; 
 int MCB_BUSY ; 
 int MCB_NON_DISPLAY_BUSY ; 
 int MCC_BUSY ; 
 int MCD_BUSY ; 
 int PA_BUSY ; 
 int PF_RQ_PENDING ; 
 int RADEON_RESET_CP ; 
 int RADEON_RESET_DISPLAY ; 
 int RADEON_RESET_DMA ; 
 int RADEON_RESET_GFX ; 
 int RADEON_RESET_GRBM ; 
 int RADEON_RESET_IH ; 
 int RADEON_RESET_MC ; 
 int RADEON_RESET_RLC ; 
 int RADEON_RESET_SEM ; 
 int RADEON_RESET_VMC ; 
 int RLC_BUSY ; 
 int RLC_RQ_PENDING ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int SC_BUSY ; 
 int SEM_BUSY ; 
 int SH_BUSY ; 
 int SPI_BUSY ; 
 int /*<<< orphan*/  SRBM_STATUS ; 
 int /*<<< orphan*/  SRBM_STATUS2 ; 
 int SX_BUSY ; 
 int TA_BUSY ; 
 int VGT_BUSY ; 
 int VGT_BUSY_NO_DMA ; 
 int VMC_BUSY ; 
 int /*<<< orphan*/  VM_L2_STATUS ; 
 scalar_t__ evergreen_is_display_hung (struct radeon_device*) ; 

__attribute__((used)) static u32 evergreen_gpu_check_soft_reset(struct radeon_device *rdev)
{
	u32 reset_mask = 0;
	u32 tmp;

	/* GRBM_STATUS */
	tmp = RREG32(GRBM_STATUS);
	if (tmp & (PA_BUSY | SC_BUSY |
		   SH_BUSY | SX_BUSY |
		   TA_BUSY | VGT_BUSY |
		   DB_BUSY | CB_BUSY |
		   SPI_BUSY | VGT_BUSY_NO_DMA))
		reset_mask |= RADEON_RESET_GFX;

	if (tmp & (CF_RQ_PENDING | PF_RQ_PENDING |
		   CP_BUSY | CP_COHERENCY_BUSY))
		reset_mask |= RADEON_RESET_CP;

	if (tmp & GRBM_EE_BUSY)
		reset_mask |= RADEON_RESET_GRBM | RADEON_RESET_GFX | RADEON_RESET_CP;

	/* DMA_STATUS_REG */
	tmp = RREG32(DMA_STATUS_REG);
	if (!(tmp & DMA_IDLE))
		reset_mask |= RADEON_RESET_DMA;

	/* SRBM_STATUS2 */
	tmp = RREG32(SRBM_STATUS2);
	if (tmp & DMA_BUSY)
		reset_mask |= RADEON_RESET_DMA;

	/* SRBM_STATUS */
	tmp = RREG32(SRBM_STATUS);
	if (tmp & (RLC_RQ_PENDING | RLC_BUSY))
		reset_mask |= RADEON_RESET_RLC;

	if (tmp & IH_BUSY)
		reset_mask |= RADEON_RESET_IH;

	if (tmp & SEM_BUSY)
		reset_mask |= RADEON_RESET_SEM;

	if (tmp & GRBM_RQ_PENDING)
		reset_mask |= RADEON_RESET_GRBM;

	if (tmp & VMC_BUSY)
		reset_mask |= RADEON_RESET_VMC;

	if (tmp & (MCB_BUSY | MCB_NON_DISPLAY_BUSY |
		   MCC_BUSY | MCD_BUSY))
		reset_mask |= RADEON_RESET_MC;

	if (evergreen_is_display_hung(rdev))
		reset_mask |= RADEON_RESET_DISPLAY;

	/* VM_L2_STATUS */
	tmp = RREG32(VM_L2_STATUS);
	if (tmp & L2_BUSY)
		reset_mask |= RADEON_RESET_VMC;

	/* Skip MC reset as it's mostly likely not hung, just busy */
	if (reset_mask & RADEON_RESET_MC) {
		DRM_DEBUG("MC busy: 0x%08X, clearing.\n", reset_mask);
		reset_mask &= ~RADEON_RESET_MC;
	}

	return reset_mask;
}