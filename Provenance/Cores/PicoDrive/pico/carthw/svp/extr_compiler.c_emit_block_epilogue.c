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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int iram_context; } ;
struct TYPE_4__ {TYPE_1__ drc; } ;

/* Variables and functions */
 int A_COND_AL ; 
 int /*<<< orphan*/  EL_ANOMALY ; 
 int /*<<< orphan*/  EOP_SUB_IMM (int,int,int /*<<< orphan*/ ,int) ; 
 int SSP_BLOCKTAB_IRAM_ONE ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  emith_call_cond (int,int /*<<< orphan*/ ) ; 
 int emith_jump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emith_jump_cond (int,int /*<<< orphan*/ *) ; 
 TYPE_2__* ssp ; 
 int /*<<< orphan*/ ** ssp_block_table ; 
 int /*<<< orphan*/ ** ssp_block_table_iram ; 
 int /*<<< orphan*/ * ssp_drc_next ; 
 int /*<<< orphan*/  ssp_drc_next_patch ; 
 void* tcache_ptr ; 
 int tr_neg_cond (int) ; 

__attribute__((used)) static void *emit_block_epilogue(int cycles, int cond, int pc, int end_pc)
{
	void *end_ptr = NULL;

	if (cycles > 0xff) {
		elprintf(EL_ANOMALY, "large cycle count: %i\n", cycles);
		cycles = 0xff;
	}
	EOP_SUB_IMM(11,11,0,cycles);		// sub r11, r11, #cycles

	if (cond < 0 || (end_pc >= 0x400 && pc < 0x400)) {
		// indirect jump, or rom -> iram jump, must use dispatcher
		emith_jump(ssp_drc_next);
	}
	else if (cond == A_COND_AL) {
		u32 *target = (pc < 0x400) ?
			ssp_block_table_iram[ssp->drc.iram_context * SSP_BLOCKTAB_IRAM_ONE + pc] :
			ssp_block_table[pc];
		if (target != NULL)
			emith_jump(target);
		else {
			int ops = emith_jump(ssp_drc_next);
			end_ptr = tcache_ptr;
			// cause the next block to be emitted over jump instruction
			tcache_ptr -= ops;
		}
	}
	else {
		u32 *target1 = (pc     < 0x400) ?
			ssp_block_table_iram[ssp->drc.iram_context * SSP_BLOCKTAB_IRAM_ONE + pc] :
			ssp_block_table[pc];
		u32 *target2 = (end_pc < 0x400) ?
			ssp_block_table_iram[ssp->drc.iram_context * SSP_BLOCKTAB_IRAM_ONE + end_pc] :
			ssp_block_table[end_pc];
		if (target1 != NULL)
		     emith_jump_cond(cond, target1);
		if (target2 != NULL)
		     emith_jump_cond(tr_neg_cond(cond), target2); // neg_cond, to be able to swap jumps if needed
#ifndef __EPOC32__
		// emit patchable branches
		if (target1 == NULL)
			emith_call_cond(cond, ssp_drc_next_patch);
		if (target2 == NULL)
			emith_call_cond(tr_neg_cond(cond), ssp_drc_next_patch);
#else
		// won't patch indirect jumps
		if (target1 == NULL || target2 == NULL)
			emith_jump(ssp_drc_next);
#endif
	}

	if (end_ptr == NULL)
		end_ptr = tcache_ptr;

	return end_ptr;
}