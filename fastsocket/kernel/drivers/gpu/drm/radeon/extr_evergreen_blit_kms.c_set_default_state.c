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
typedef  int u64 ;
typedef  int u32 ;
struct radeon_ring {int dummy; } ;
struct TYPE_2__ {int shader_gpu_addr; int state_offset; int /*<<< orphan*/  state_len; } ;
struct radeon_device {int family; TYPE_1__ r600_blit; struct radeon_ring* ring; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int) ; 
#define  CHIP_BARTS 138 
#define  CHIP_CAICOS 137 
 int CHIP_CAYMAN ; 
#define  CHIP_CEDAR 136 
#define  CHIP_CYPRESS 135 
#define  CHIP_HEMLOCK 134 
#define  CHIP_JUNIPER 133 
#define  CHIP_PALM 132 
#define  CHIP_REDWOOD 131 
#define  CHIP_SUMO 130 
#define  CHIP_SUMO2 129 
#define  CHIP_TURKS 128 
 int CS_PRIO (int /*<<< orphan*/ ) ; 
 int ES_PRIO (int) ; 
 int EXPORT_SRC_C ; 
 int GS_PRIO (int) ; 
 int HS_PRIO (int /*<<< orphan*/ ) ; 
 int LS_PRIO (int /*<<< orphan*/ ) ; 
 int NUM_CLAUSE_TEMP_GPRS (int) ; 
 int NUM_ES_GPRS (int) ; 
 int NUM_ES_STACK_ENTRIES (int) ; 
 int NUM_ES_THREADS (int) ; 
 int NUM_GS_GPRS (int) ; 
 int NUM_GS_STACK_ENTRIES (int) ; 
 int NUM_GS_THREADS (int) ; 
 int NUM_HS_GPRS (int) ; 
 int NUM_HS_STACK_ENTRIES (int) ; 
 int NUM_HS_THREADS (int) ; 
 int NUM_LS_GPRS (int) ; 
 int NUM_LS_STACK_ENTRIES (int) ; 
 int NUM_LS_THREADS (int) ; 
 int NUM_PS_GPRS (int) ; 
 int NUM_PS_STACK_ENTRIES (int) ; 
 int NUM_PS_THREADS (int) ; 
 int NUM_VS_GPRS (int) ; 
 int NUM_VS_STACK_ENTRIES (int) ; 
 int NUM_VS_THREADS (int) ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_CLEAR_STATE ; 
 int /*<<< orphan*/  PACKET3_INDIRECT_BUFFER ; 
 int /*<<< orphan*/  PACKET3_MODE_CONTROL ; 
 int /*<<< orphan*/  PACKET3_SET_CONFIG_REG ; 
 int PACKET3_SET_CONFIG_REG_START ; 
 int PS_PRIO (int /*<<< orphan*/ ) ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int SQ_CONFIG ; 
 int SQ_DYN_GPR_CNTL_PS_FLUSH_REQ ; 
 int SQ_LDS_RESOURCE_MGMT ; 
 int VC_ENABLE ; 
 int VS_PRIO (int) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void
set_default_state(struct radeon_device *rdev)
{
	struct radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	u32 sq_config, sq_gpr_resource_mgmt_1, sq_gpr_resource_mgmt_2, sq_gpr_resource_mgmt_3;
	u32 sq_thread_resource_mgmt, sq_thread_resource_mgmt_2;
	u32 sq_stack_resource_mgmt_1, sq_stack_resource_mgmt_2, sq_stack_resource_mgmt_3;
	int num_ps_gprs, num_vs_gprs, num_temp_gprs;
	int num_gs_gprs, num_es_gprs, num_hs_gprs, num_ls_gprs;
	int num_ps_threads, num_vs_threads, num_gs_threads, num_es_threads;
	int num_hs_threads, num_ls_threads;
	int num_ps_stack_entries, num_vs_stack_entries, num_gs_stack_entries, num_es_stack_entries;
	int num_hs_stack_entries, num_ls_stack_entries;
	u64 gpu_addr;
	int dwords;

	/* set clear context state */
	radeon_ring_write(ring, PACKET3(PACKET3_CLEAR_STATE, 0));
	radeon_ring_write(ring, 0);

	if (rdev->family < CHIP_CAYMAN) {
		switch (rdev->family) {
		case CHIP_CEDAR:
		default:
			num_ps_gprs = 93;
			num_vs_gprs = 46;
			num_temp_gprs = 4;
			num_gs_gprs = 31;
			num_es_gprs = 31;
			num_hs_gprs = 23;
			num_ls_gprs = 23;
			num_ps_threads = 96;
			num_vs_threads = 16;
			num_gs_threads = 16;
			num_es_threads = 16;
			num_hs_threads = 16;
			num_ls_threads = 16;
			num_ps_stack_entries = 42;
			num_vs_stack_entries = 42;
			num_gs_stack_entries = 42;
			num_es_stack_entries = 42;
			num_hs_stack_entries = 42;
			num_ls_stack_entries = 42;
			break;
		case CHIP_REDWOOD:
			num_ps_gprs = 93;
			num_vs_gprs = 46;
			num_temp_gprs = 4;
			num_gs_gprs = 31;
			num_es_gprs = 31;
			num_hs_gprs = 23;
			num_ls_gprs = 23;
			num_ps_threads = 128;
			num_vs_threads = 20;
			num_gs_threads = 20;
			num_es_threads = 20;
			num_hs_threads = 20;
			num_ls_threads = 20;
			num_ps_stack_entries = 42;
			num_vs_stack_entries = 42;
			num_gs_stack_entries = 42;
			num_es_stack_entries = 42;
			num_hs_stack_entries = 42;
			num_ls_stack_entries = 42;
			break;
		case CHIP_JUNIPER:
			num_ps_gprs = 93;
			num_vs_gprs = 46;
			num_temp_gprs = 4;
			num_gs_gprs = 31;
			num_es_gprs = 31;
			num_hs_gprs = 23;
			num_ls_gprs = 23;
			num_ps_threads = 128;
			num_vs_threads = 20;
			num_gs_threads = 20;
			num_es_threads = 20;
			num_hs_threads = 20;
			num_ls_threads = 20;
			num_ps_stack_entries = 85;
			num_vs_stack_entries = 85;
			num_gs_stack_entries = 85;
			num_es_stack_entries = 85;
			num_hs_stack_entries = 85;
			num_ls_stack_entries = 85;
			break;
		case CHIP_CYPRESS:
		case CHIP_HEMLOCK:
			num_ps_gprs = 93;
			num_vs_gprs = 46;
			num_temp_gprs = 4;
			num_gs_gprs = 31;
			num_es_gprs = 31;
			num_hs_gprs = 23;
			num_ls_gprs = 23;
			num_ps_threads = 128;
			num_vs_threads = 20;
			num_gs_threads = 20;
			num_es_threads = 20;
			num_hs_threads = 20;
			num_ls_threads = 20;
			num_ps_stack_entries = 85;
			num_vs_stack_entries = 85;
			num_gs_stack_entries = 85;
			num_es_stack_entries = 85;
			num_hs_stack_entries = 85;
			num_ls_stack_entries = 85;
			break;
		case CHIP_PALM:
			num_ps_gprs = 93;
			num_vs_gprs = 46;
			num_temp_gprs = 4;
			num_gs_gprs = 31;
			num_es_gprs = 31;
			num_hs_gprs = 23;
			num_ls_gprs = 23;
			num_ps_threads = 96;
			num_vs_threads = 16;
			num_gs_threads = 16;
			num_es_threads = 16;
			num_hs_threads = 16;
			num_ls_threads = 16;
			num_ps_stack_entries = 42;
			num_vs_stack_entries = 42;
			num_gs_stack_entries = 42;
			num_es_stack_entries = 42;
			num_hs_stack_entries = 42;
			num_ls_stack_entries = 42;
			break;
		case CHIP_SUMO:
			num_ps_gprs = 93;
			num_vs_gprs = 46;
			num_temp_gprs = 4;
			num_gs_gprs = 31;
			num_es_gprs = 31;
			num_hs_gprs = 23;
			num_ls_gprs = 23;
			num_ps_threads = 96;
			num_vs_threads = 25;
			num_gs_threads = 25;
			num_es_threads = 25;
			num_hs_threads = 25;
			num_ls_threads = 25;
			num_ps_stack_entries = 42;
			num_vs_stack_entries = 42;
			num_gs_stack_entries = 42;
			num_es_stack_entries = 42;
			num_hs_stack_entries = 42;
			num_ls_stack_entries = 42;
			break;
		case CHIP_SUMO2:
			num_ps_gprs = 93;
			num_vs_gprs = 46;
			num_temp_gprs = 4;
			num_gs_gprs = 31;
			num_es_gprs = 31;
			num_hs_gprs = 23;
			num_ls_gprs = 23;
			num_ps_threads = 96;
			num_vs_threads = 25;
			num_gs_threads = 25;
			num_es_threads = 25;
			num_hs_threads = 25;
			num_ls_threads = 25;
			num_ps_stack_entries = 85;
			num_vs_stack_entries = 85;
			num_gs_stack_entries = 85;
			num_es_stack_entries = 85;
			num_hs_stack_entries = 85;
			num_ls_stack_entries = 85;
			break;
		case CHIP_BARTS:
			num_ps_gprs = 93;
			num_vs_gprs = 46;
			num_temp_gprs = 4;
			num_gs_gprs = 31;
			num_es_gprs = 31;
			num_hs_gprs = 23;
			num_ls_gprs = 23;
			num_ps_threads = 128;
			num_vs_threads = 20;
			num_gs_threads = 20;
			num_es_threads = 20;
			num_hs_threads = 20;
			num_ls_threads = 20;
			num_ps_stack_entries = 85;
			num_vs_stack_entries = 85;
			num_gs_stack_entries = 85;
			num_es_stack_entries = 85;
			num_hs_stack_entries = 85;
			num_ls_stack_entries = 85;
			break;
		case CHIP_TURKS:
			num_ps_gprs = 93;
			num_vs_gprs = 46;
			num_temp_gprs = 4;
			num_gs_gprs = 31;
			num_es_gprs = 31;
			num_hs_gprs = 23;
			num_ls_gprs = 23;
			num_ps_threads = 128;
			num_vs_threads = 20;
			num_gs_threads = 20;
			num_es_threads = 20;
			num_hs_threads = 20;
			num_ls_threads = 20;
			num_ps_stack_entries = 42;
			num_vs_stack_entries = 42;
			num_gs_stack_entries = 42;
			num_es_stack_entries = 42;
			num_hs_stack_entries = 42;
			num_ls_stack_entries = 42;
			break;
		case CHIP_CAICOS:
			num_ps_gprs = 93;
			num_vs_gprs = 46;
			num_temp_gprs = 4;
			num_gs_gprs = 31;
			num_es_gprs = 31;
			num_hs_gprs = 23;
			num_ls_gprs = 23;
			num_ps_threads = 128;
			num_vs_threads = 10;
			num_gs_threads = 10;
			num_es_threads = 10;
			num_hs_threads = 10;
			num_ls_threads = 10;
			num_ps_stack_entries = 42;
			num_vs_stack_entries = 42;
			num_gs_stack_entries = 42;
			num_es_stack_entries = 42;
			num_hs_stack_entries = 42;
			num_ls_stack_entries = 42;
			break;
		}

		if ((rdev->family == CHIP_CEDAR) ||
		    (rdev->family == CHIP_PALM) ||
		    (rdev->family == CHIP_SUMO) ||
		    (rdev->family == CHIP_SUMO2) ||
		    (rdev->family == CHIP_CAICOS))
			sq_config = 0;
		else
			sq_config = VC_ENABLE;

		sq_config |= (EXPORT_SRC_C |
			      CS_PRIO(0) |
			      LS_PRIO(0) |
			      HS_PRIO(0) |
			      PS_PRIO(0) |
			      VS_PRIO(1) |
			      GS_PRIO(2) |
			      ES_PRIO(3));

		sq_gpr_resource_mgmt_1 = (NUM_PS_GPRS(num_ps_gprs) |
					  NUM_VS_GPRS(num_vs_gprs) |
					  NUM_CLAUSE_TEMP_GPRS(num_temp_gprs));
		sq_gpr_resource_mgmt_2 = (NUM_GS_GPRS(num_gs_gprs) |
					  NUM_ES_GPRS(num_es_gprs));
		sq_gpr_resource_mgmt_3 = (NUM_HS_GPRS(num_hs_gprs) |
					  NUM_LS_GPRS(num_ls_gprs));
		sq_thread_resource_mgmt = (NUM_PS_THREADS(num_ps_threads) |
					   NUM_VS_THREADS(num_vs_threads) |
					   NUM_GS_THREADS(num_gs_threads) |
					   NUM_ES_THREADS(num_es_threads));
		sq_thread_resource_mgmt_2 = (NUM_HS_THREADS(num_hs_threads) |
					     NUM_LS_THREADS(num_ls_threads));
		sq_stack_resource_mgmt_1 = (NUM_PS_STACK_ENTRIES(num_ps_stack_entries) |
					    NUM_VS_STACK_ENTRIES(num_vs_stack_entries));
		sq_stack_resource_mgmt_2 = (NUM_GS_STACK_ENTRIES(num_gs_stack_entries) |
					    NUM_ES_STACK_ENTRIES(num_es_stack_entries));
		sq_stack_resource_mgmt_3 = (NUM_HS_STACK_ENTRIES(num_hs_stack_entries) |
					    NUM_LS_STACK_ENTRIES(num_ls_stack_entries));

		/* disable dyn gprs */
		radeon_ring_write(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
		radeon_ring_write(ring, (SQ_DYN_GPR_CNTL_PS_FLUSH_REQ - PACKET3_SET_CONFIG_REG_START) >> 2);
		radeon_ring_write(ring, 0);

		/* setup LDS */
		radeon_ring_write(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
		radeon_ring_write(ring, (SQ_LDS_RESOURCE_MGMT - PACKET3_SET_CONFIG_REG_START) >> 2);
		radeon_ring_write(ring, 0x10001000);

		/* SQ config */
		radeon_ring_write(ring, PACKET3(PACKET3_SET_CONFIG_REG, 11));
		radeon_ring_write(ring, (SQ_CONFIG - PACKET3_SET_CONFIG_REG_START) >> 2);
		radeon_ring_write(ring, sq_config);
		radeon_ring_write(ring, sq_gpr_resource_mgmt_1);
		radeon_ring_write(ring, sq_gpr_resource_mgmt_2);
		radeon_ring_write(ring, sq_gpr_resource_mgmt_3);
		radeon_ring_write(ring, 0);
		radeon_ring_write(ring, 0);
		radeon_ring_write(ring, sq_thread_resource_mgmt);
		radeon_ring_write(ring, sq_thread_resource_mgmt_2);
		radeon_ring_write(ring, sq_stack_resource_mgmt_1);
		radeon_ring_write(ring, sq_stack_resource_mgmt_2);
		radeon_ring_write(ring, sq_stack_resource_mgmt_3);
	}

	/* CONTEXT_CONTROL */
	radeon_ring_write(ring, 0xc0012800);
	radeon_ring_write(ring, 0x80000000);
	radeon_ring_write(ring, 0x80000000);

	/* SQ_VTX_BASE_VTX_LOC */
	radeon_ring_write(ring, 0xc0026f00);
	radeon_ring_write(ring, 0x00000000);
	radeon_ring_write(ring, 0x00000000);
	radeon_ring_write(ring, 0x00000000);

	/* SET_SAMPLER */
	radeon_ring_write(ring, 0xc0036e00);
	radeon_ring_write(ring, 0x00000000);
	radeon_ring_write(ring, 0x00000012);
	radeon_ring_write(ring, 0x00000000);
	radeon_ring_write(ring, 0x00000000);

	/* set to DX10/11 mode */
	radeon_ring_write(ring, PACKET3(PACKET3_MODE_CONTROL, 0));
	radeon_ring_write(ring, 1);

	/* emit an IB pointing at default state */
	dwords = ALIGN(rdev->r600_blit.state_len, 0x10);
	gpu_addr = rdev->r600_blit.shader_gpu_addr + rdev->r600_blit.state_offset;
	radeon_ring_write(ring, PACKET3(PACKET3_INDIRECT_BUFFER, 2));
	radeon_ring_write(ring, gpu_addr & 0xFFFFFFFC);
	radeon_ring_write(ring, upper_32_bits(gpu_addr) & 0xFF);
	radeon_ring_write(ring, dwords);

}