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
 int /*<<< orphan*/  CPU_INSTR_MODE ; 
 int CPU_PREF_ADDR ; 
 int /*<<< orphan*/  CPU_RUN_MODE ; 
 scalar_t__ CPU_STOPPED ; 
 int FLAG_INT_MASK ; 
 scalar_t__ FLAG_T0 ; 
 scalar_t__ FLAG_T1 ; 
 int /*<<< orphan*/  INSTRUCTION_YES ; 
 int MFLAG_CLEAR ; 
 void* REG_PC ; 
 void* REG_SP ; 
 scalar_t__ REG_VBR ; 
 int /*<<< orphan*/  RUN_MODE_BERR_AERR_RESET ; 
 int /*<<< orphan*/  RUN_MODE_NORMAL ; 
 int /*<<< orphan*/  SET_CYCLES (int /*<<< orphan*/ ) ; 
 int SFLAG_SET ; 
 int /*<<< orphan*/  m68ki_clear_trace () ; 
 int /*<<< orphan*/  m68ki_jump (void*) ; 
 void* m68ki_read_imm_32 () ; 
 int /*<<< orphan*/  m68ki_set_sm_flag (int) ; 

void m68k_pulse_reset(void)
{
	/* Clear all stop levels and eat up all remaining cycles */
	CPU_STOPPED = 0;
	SET_CYCLES(0);

	CPU_RUN_MODE = RUN_MODE_BERR_AERR_RESET;
	CPU_INSTR_MODE = INSTRUCTION_YES;

	/* Turn off tracing */
	FLAG_T1 = FLAG_T0 = 0;
	m68ki_clear_trace();
	/* Interrupt mask to level 7 */
	FLAG_INT_MASK = 0x0700;
	/* Reset VBR */
	REG_VBR = 0;
	/* Go to supervisor mode */
	m68ki_set_sm_flag(SFLAG_SET | MFLAG_CLEAR);

	/* Invalidate the prefetch queue */
#if M68K_EMULATE_PREFETCH
	/* Set to arbitrary number since our first fetch is from 0 */
	CPU_PREF_ADDR = 0x1000;
#endif /* M68K_EMULATE_PREFETCH */

	/* Read the initial stack pointer and program counter */
	m68ki_jump(0);
	REG_SP = m68ki_read_imm_32();
	REG_PC = m68ki_read_imm_32();
	m68ki_jump(REG_PC);

	CPU_RUN_MODE = RUN_MODE_NORMAL;
}