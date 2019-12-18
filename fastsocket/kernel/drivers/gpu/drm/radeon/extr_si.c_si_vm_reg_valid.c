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

/* Variables and functions */
#define  CP_STRMOUT_CNTL 153 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
#define  GRBM_GFX_INDEX 152 
#define  PA_CL_ENHANCE 151 
#define  PA_SC_ENHANCE 150 
#define  PA_SC_LINE_STIPPLE_STATE 149 
#define  PA_SU_LINE_STIPPLE_VALUE 148 
#define  SPI_CONFIG_CNTL 147 
#define  SPI_CONFIG_CNTL_1 146 
#define  SPI_PS_MAX_WAVE_ID 145 
#define  SPI_STATIC_THREAD_MGMT_1 144 
#define  SPI_STATIC_THREAD_MGMT_2 143 
#define  SPI_STATIC_THREAD_MGMT_3 142 
#define  SQC_CACHES 141 
#define  TA_CNTL_AUX 140 
#define  VGT_CACHE_INVALIDATION 139 
#define  VGT_ESGS_RING_SIZE 138 
#define  VGT_GSVS_RING_SIZE 137 
#define  VGT_GS_VERTEX_REUSE 136 
#define  VGT_HS_OFFCHIP_PARAM 135 
#define  VGT_INDEX_TYPE 134 
#define  VGT_NUM_INDICES 133 
#define  VGT_NUM_INSTANCES 132 
#define  VGT_PRIMITIVE_TYPE 131 
#define  VGT_TF_MEMORY_BASE 130 
#define  VGT_TF_RING_SIZE 129 
#define  VGT_VTX_VECT_EJECT_REG 128 

__attribute__((used)) static bool si_vm_reg_valid(u32 reg)
{
	/* context regs are fine */
	if (reg >= 0x28000)
		return true;

	/* check config regs */
	switch (reg) {
	case GRBM_GFX_INDEX:
	case CP_STRMOUT_CNTL:
	case VGT_VTX_VECT_EJECT_REG:
	case VGT_CACHE_INVALIDATION:
	case VGT_ESGS_RING_SIZE:
	case VGT_GSVS_RING_SIZE:
	case VGT_GS_VERTEX_REUSE:
	case VGT_PRIMITIVE_TYPE:
	case VGT_INDEX_TYPE:
	case VGT_NUM_INDICES:
	case VGT_NUM_INSTANCES:
	case VGT_TF_RING_SIZE:
	case VGT_HS_OFFCHIP_PARAM:
	case VGT_TF_MEMORY_BASE:
	case PA_CL_ENHANCE:
	case PA_SU_LINE_STIPPLE_VALUE:
	case PA_SC_LINE_STIPPLE_STATE:
	case PA_SC_ENHANCE:
	case SQC_CACHES:
	case SPI_STATIC_THREAD_MGMT_1:
	case SPI_STATIC_THREAD_MGMT_2:
	case SPI_STATIC_THREAD_MGMT_3:
	case SPI_PS_MAX_WAVE_ID:
	case SPI_CONFIG_CNTL:
	case SPI_CONFIG_CNTL_1:
	case TA_CNTL_AUX:
		return true;
	default:
		DRM_ERROR("Invalid register 0x%x in CS\n", reg);
		return false;
	}
}