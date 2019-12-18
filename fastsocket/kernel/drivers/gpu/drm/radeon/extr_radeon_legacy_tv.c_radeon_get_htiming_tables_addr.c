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
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int RADEON_HCODE_TABLE_SEL_MASK ; 
 int RADEON_HCODE_TABLE_SEL_SHIFT ; 
 int RADEON_TABLE1_BOT_ADR_MASK ; 
 int RADEON_TABLE1_BOT_ADR_SHIFT ; 
 int RADEON_TABLE3_TOP_ADR_MASK ; 
 int RADEON_TABLE3_TOP_ADR_SHIFT ; 
 int RADEON_TV_MAX_FIFO_ADDR_INTERNAL ; 

__attribute__((used)) static uint16_t radeon_get_htiming_tables_addr(uint32_t tv_uv_adr)
{
	uint16_t h_table;

	switch ((tv_uv_adr & RADEON_HCODE_TABLE_SEL_MASK) >> RADEON_HCODE_TABLE_SEL_SHIFT) {
	case 0:
		h_table = RADEON_TV_MAX_FIFO_ADDR_INTERNAL;
		break;
	case 1:
		h_table = ((tv_uv_adr & RADEON_TABLE1_BOT_ADR_MASK) >> RADEON_TABLE1_BOT_ADR_SHIFT) * 2;
		break;
	case 2:
		h_table = ((tv_uv_adr & RADEON_TABLE3_TOP_ADR_MASK) >> RADEON_TABLE3_TOP_ADR_SHIFT) * 2;
		break;
	default:
		h_table = 0;
		break;
	}
	return h_table;
}