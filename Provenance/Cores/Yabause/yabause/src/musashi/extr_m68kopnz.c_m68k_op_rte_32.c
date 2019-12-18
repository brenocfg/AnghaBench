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
typedef  int uint ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_INSTR_MODE ; 
 int /*<<< orphan*/  CPU_RUN_MODE ; 
 int /*<<< orphan*/  CPU_TYPE ; 
 scalar_t__ CPU_TYPE_IS_000 (int /*<<< orphan*/ ) ; 
 scalar_t__ CPU_TYPE_IS_010 (int /*<<< orphan*/ ) ; 
 scalar_t__ FLAG_S ; 
 int /*<<< orphan*/  INSTRUCTION_YES ; 
 scalar_t__* REG_A ; 
 int /*<<< orphan*/  RUN_MODE_NORMAL ; 
 int /*<<< orphan*/  m68ki_exception_format_error () ; 
 int /*<<< orphan*/  m68ki_exception_privilege_violation () ; 
 int /*<<< orphan*/  m68ki_fake_pull_16 () ; 
 int /*<<< orphan*/  m68ki_fake_pull_32 () ; 
 int /*<<< orphan*/  m68ki_jump (int) ; 
 int m68ki_pull_16 () ; 
 int m68ki_pull_32 () ; 
 int m68ki_read_16 (scalar_t__) ; 
 int /*<<< orphan*/  m68ki_set_sr (int) ; 
 int /*<<< orphan*/  m68ki_set_sr_noint (int) ; 
 int /*<<< orphan*/  m68ki_trace_t0 () ; 

void m68k_op_rte_32(void)
{
	if(FLAG_S)
	{
		uint new_sr;
		uint new_pc;
		uint format_word;

		m68ki_trace_t0();			   /* auto-disable (see m68kcpu.h) */

		if(CPU_TYPE_IS_000(CPU_TYPE))
		{
			new_sr = m68ki_pull_16();
			new_pc = m68ki_pull_32();
			m68ki_jump(new_pc);
			m68ki_set_sr(new_sr);

			CPU_INSTR_MODE = INSTRUCTION_YES;
			CPU_RUN_MODE = RUN_MODE_NORMAL;

			return;
		}

		if(CPU_TYPE_IS_010(CPU_TYPE))
		{
			format_word = m68ki_read_16(REG_A[7]+6) >> 12;
			if(format_word == 0)
			{
				new_sr = m68ki_pull_16();
				new_pc = m68ki_pull_32();
				m68ki_fake_pull_16();	/* format word */
				m68ki_jump(new_pc);
				m68ki_set_sr(new_sr);
				CPU_INSTR_MODE = INSTRUCTION_YES;
				CPU_RUN_MODE = RUN_MODE_NORMAL;
				return;
			}
			CPU_INSTR_MODE = INSTRUCTION_YES;
			CPU_RUN_MODE = RUN_MODE_NORMAL;
			/* Not handling bus fault (9) */
			m68ki_exception_format_error();
			return;
		}

		/* Otherwise it's 020 */
rte_loop:
		format_word = m68ki_read_16(REG_A[7]+6) >> 12;
		switch(format_word)
		{
			case 0: /* Normal */
				new_sr = m68ki_pull_16();
				new_pc = m68ki_pull_32();
				m68ki_fake_pull_16();	/* format word */
				m68ki_jump(new_pc);
				m68ki_set_sr(new_sr);
				CPU_INSTR_MODE = INSTRUCTION_YES;
				CPU_RUN_MODE = RUN_MODE_NORMAL;
				return;
			case 1: /* Throwaway */
				new_sr = m68ki_pull_16();
				m68ki_fake_pull_32();	/* program counter */
				m68ki_fake_pull_16();	/* format word */
				m68ki_set_sr_noint(new_sr);
				goto rte_loop;
			case 2: /* Trap */
				new_sr = m68ki_pull_16();
				new_pc = m68ki_pull_32();
				m68ki_fake_pull_16();	/* format word */
				m68ki_fake_pull_32();	/* address */
				m68ki_jump(new_pc);
				m68ki_set_sr(new_sr);
				CPU_INSTR_MODE = INSTRUCTION_YES;
				CPU_RUN_MODE = RUN_MODE_NORMAL;
				return;
		}
		/* Not handling long or short bus fault */
		CPU_INSTR_MODE = INSTRUCTION_YES;
		CPU_RUN_MODE = RUN_MODE_NORMAL;
		m68ki_exception_format_error();
		return;
	}
	m68ki_exception_privilege_violation();
}