#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
#define  CHIP_R600 139 
#define  CHIP_RS780 138 
#define  CHIP_RS880 137 
#define  CHIP_RV610 136 
#define  CHIP_RV620 135 
#define  CHIP_RV630 134 
#define  CHIP_RV635 133 
#define  CHIP_RV670 132 
#define  CHIP_RV710 131 
#define  CHIP_RV730 130 
#define  CHIP_RV740 129 
#define  CHIP_RV770 128 
 int CP_PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int R600_ALU_INST_PREFER_VECTOR ; 
 int R600_CACHE_FLUSH_AND_INV_EVENT ; 
 int R600_DX9_CONSTS ; 
 int R600_ES_PRIO (int) ; 
 int R600_GS_PRIO (int) ; 
 int /*<<< orphan*/  R600_IT_EVENT_WRITE ; 
 int /*<<< orphan*/  R600_IT_SET_CONFIG_REG ; 
 int R600_NUM_CLAUSE_TEMP_GPRS (int) ; 
 int R600_NUM_ES_GPRS (int) ; 
 int R600_NUM_ES_STACK_ENTRIES (int) ; 
 int R600_NUM_ES_THREADS (int) ; 
 int R600_NUM_GS_GPRS (int) ; 
 int R600_NUM_GS_STACK_ENTRIES (int) ; 
 int R600_NUM_GS_THREADS (int) ; 
 int R600_NUM_PS_GPRS (int) ; 
 int R600_NUM_PS_STACK_ENTRIES (int) ; 
 int R600_NUM_PS_THREADS (int) ; 
 int R600_NUM_VS_GPRS (int) ; 
 int R600_NUM_VS_STACK_ENTRIES (int) ; 
 int R600_NUM_VS_THREADS (int) ; 
 int R600_PS_PRIO (int /*<<< orphan*/ ) ; 
 int R600_SET_CONFIG_REG_OFFSET ; 
 int R600_SQ_CONFIG ; 
 int R600_VC_ENABLE ; 
 int R600_VS_PRIO (int) ; 
 int RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int r6xx_default_size ; 
 int* r6xx_default_state ; 
 int r7xx_default_size ; 
 int* r7xx_default_state ; 

__attribute__((used)) static void
set_default_state(drm_radeon_private_t *dev_priv)
{
	int i;
	u32 sq_config, sq_gpr_resource_mgmt_1, sq_gpr_resource_mgmt_2;
	u32 sq_thread_resource_mgmt, sq_stack_resource_mgmt_1, sq_stack_resource_mgmt_2;
	int num_ps_gprs, num_vs_gprs, num_temp_gprs, num_gs_gprs, num_es_gprs;
	int num_ps_threads, num_vs_threads, num_gs_threads, num_es_threads;
	int num_ps_stack_entries, num_vs_stack_entries, num_gs_stack_entries, num_es_stack_entries;
	RING_LOCALS;

	switch ((dev_priv->flags & RADEON_FAMILY_MASK)) {
	case CHIP_R600:
		num_ps_gprs = 192;
		num_vs_gprs = 56;
		num_temp_gprs = 4;
		num_gs_gprs = 0;
		num_es_gprs = 0;
		num_ps_threads = 136;
		num_vs_threads = 48;
		num_gs_threads = 4;
		num_es_threads = 4;
		num_ps_stack_entries = 128;
		num_vs_stack_entries = 128;
		num_gs_stack_entries = 0;
		num_es_stack_entries = 0;
		break;
	case CHIP_RV630:
	case CHIP_RV635:
		num_ps_gprs = 84;
		num_vs_gprs = 36;
		num_temp_gprs = 4;
		num_gs_gprs = 0;
		num_es_gprs = 0;
		num_ps_threads = 144;
		num_vs_threads = 40;
		num_gs_threads = 4;
		num_es_threads = 4;
		num_ps_stack_entries = 40;
		num_vs_stack_entries = 40;
		num_gs_stack_entries = 32;
		num_es_stack_entries = 16;
		break;
	case CHIP_RV610:
	case CHIP_RV620:
	case CHIP_RS780:
	case CHIP_RS880:
	default:
		num_ps_gprs = 84;
		num_vs_gprs = 36;
		num_temp_gprs = 4;
		num_gs_gprs = 0;
		num_es_gprs = 0;
		num_ps_threads = 136;
		num_vs_threads = 48;
		num_gs_threads = 4;
		num_es_threads = 4;
		num_ps_stack_entries = 40;
		num_vs_stack_entries = 40;
		num_gs_stack_entries = 32;
		num_es_stack_entries = 16;
		break;
	case CHIP_RV670:
		num_ps_gprs = 144;
		num_vs_gprs = 40;
		num_temp_gprs = 4;
		num_gs_gprs = 0;
		num_es_gprs = 0;
		num_ps_threads = 136;
		num_vs_threads = 48;
		num_gs_threads = 4;
		num_es_threads = 4;
		num_ps_stack_entries = 40;
		num_vs_stack_entries = 40;
		num_gs_stack_entries = 32;
		num_es_stack_entries = 16;
		break;
	case CHIP_RV770:
		num_ps_gprs = 192;
		num_vs_gprs = 56;
		num_temp_gprs = 4;
		num_gs_gprs = 0;
		num_es_gprs = 0;
		num_ps_threads = 188;
		num_vs_threads = 60;
		num_gs_threads = 0;
		num_es_threads = 0;
		num_ps_stack_entries = 256;
		num_vs_stack_entries = 256;
		num_gs_stack_entries = 0;
		num_es_stack_entries = 0;
		break;
	case CHIP_RV730:
	case CHIP_RV740:
		num_ps_gprs = 84;
		num_vs_gprs = 36;
		num_temp_gprs = 4;
		num_gs_gprs = 0;
		num_es_gprs = 0;
		num_ps_threads = 188;
		num_vs_threads = 60;
		num_gs_threads = 0;
		num_es_threads = 0;
		num_ps_stack_entries = 128;
		num_vs_stack_entries = 128;
		num_gs_stack_entries = 0;
		num_es_stack_entries = 0;
		break;
	case CHIP_RV710:
		num_ps_gprs = 192;
		num_vs_gprs = 56;
		num_temp_gprs = 4;
		num_gs_gprs = 0;
		num_es_gprs = 0;
		num_ps_threads = 144;
		num_vs_threads = 48;
		num_gs_threads = 0;
		num_es_threads = 0;
		num_ps_stack_entries = 128;
		num_vs_stack_entries = 128;
		num_gs_stack_entries = 0;
		num_es_stack_entries = 0;
		break;
	}

	if (((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RV610) ||
	    ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RV620) ||
	    ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS780) ||
	    ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS880) ||
	    ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RV710))
		sq_config = 0;
	else
		sq_config = R600_VC_ENABLE;

	sq_config |= (R600_DX9_CONSTS |
		      R600_ALU_INST_PREFER_VECTOR |
		      R600_PS_PRIO(0) |
		      R600_VS_PRIO(1) |
		      R600_GS_PRIO(2) |
		      R600_ES_PRIO(3));

	sq_gpr_resource_mgmt_1 = (R600_NUM_PS_GPRS(num_ps_gprs) |
				  R600_NUM_VS_GPRS(num_vs_gprs) |
				  R600_NUM_CLAUSE_TEMP_GPRS(num_temp_gprs));
	sq_gpr_resource_mgmt_2 = (R600_NUM_GS_GPRS(num_gs_gprs) |
				  R600_NUM_ES_GPRS(num_es_gprs));
	sq_thread_resource_mgmt = (R600_NUM_PS_THREADS(num_ps_threads) |
				   R600_NUM_VS_THREADS(num_vs_threads) |
				   R600_NUM_GS_THREADS(num_gs_threads) |
				   R600_NUM_ES_THREADS(num_es_threads));
	sq_stack_resource_mgmt_1 = (R600_NUM_PS_STACK_ENTRIES(num_ps_stack_entries) |
				    R600_NUM_VS_STACK_ENTRIES(num_vs_stack_entries));
	sq_stack_resource_mgmt_2 = (R600_NUM_GS_STACK_ENTRIES(num_gs_stack_entries) |
				    R600_NUM_ES_STACK_ENTRIES(num_es_stack_entries));

	if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_RV770) {
		BEGIN_RING(r7xx_default_size + 10);
		for (i = 0; i < r7xx_default_size; i++)
			OUT_RING(r7xx_default_state[i]);
	} else {
		BEGIN_RING(r6xx_default_size + 10);
		for (i = 0; i < r6xx_default_size; i++)
			OUT_RING(r6xx_default_state[i]);
	}
	OUT_RING(CP_PACKET3(R600_IT_EVENT_WRITE, 0));
	OUT_RING(R600_CACHE_FLUSH_AND_INV_EVENT);
	/* SQ config */
	OUT_RING(CP_PACKET3(R600_IT_SET_CONFIG_REG, 6));
	OUT_RING((R600_SQ_CONFIG - R600_SET_CONFIG_REG_OFFSET) >> 2);
	OUT_RING(sq_config);
	OUT_RING(sq_gpr_resource_mgmt_1);
	OUT_RING(sq_gpr_resource_mgmt_2);
	OUT_RING(sq_thread_resource_mgmt);
	OUT_RING(sq_stack_resource_mgmt_1);
	OUT_RING(sq_stack_resource_mgmt_2);
	ADVANCE_RING();
}