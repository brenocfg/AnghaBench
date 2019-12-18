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

/* Variables and functions */
 int /*<<< orphan*/  A_COND_LE ; 
 int /*<<< orphan*/  EOP_CMP_IMM (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emith_jump_cond (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssp_drc_end ; 

__attribute__((used)) static void emit_block_prologue(void)
{
	// check if there are enough cycles..
	// note: r0 must contain PC of current block
	EOP_CMP_IMM(11,0,0);			// cmp r11, #0
	emith_jump_cond(A_COND_LE, ssp_drc_end);
}