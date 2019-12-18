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
 scalar_t__ BIT_B (int) ; 
 int /*<<< orphan*/  CPU_TYPE ; 
 scalar_t__ CPU_TYPE_IS_010_PLUS (int /*<<< orphan*/ ) ; 
 scalar_t__ CPU_TYPE_IS_020_VARIANT (int /*<<< orphan*/ ) ; 
 int EA_AW_32 () ; 
 scalar_t__ FLAG_S ; 
 int OPER_I_16 () ; 
 int /*<<< orphan*/ * REG_DA ; 
 int /*<<< orphan*/  REG_DFC ; 
 int /*<<< orphan*/  REG_SFC ; 
 int /*<<< orphan*/  USE_CYCLES (int) ; 
 int /*<<< orphan*/  m68ki_exception_illegal () ; 
 int /*<<< orphan*/  m68ki_exception_privilege_violation () ; 
 int /*<<< orphan*/  m68ki_read_32_fc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m68ki_trace_t0 () ; 
 int /*<<< orphan*/  m68ki_write_32_fc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void m68k_op_moves_32_aw(void)
{
	if(CPU_TYPE_IS_010_PLUS(CPU_TYPE))
	{
		if(FLAG_S)
		{
			uint word2 = OPER_I_16();
			uint ea = EA_AW_32();

			m68ki_trace_t0();			   /* auto-disable (see m68kcpu.h) */
			if(BIT_B(word2))		   /* Register to memory */
			{
				m68ki_write_32_fc(ea, REG_DFC, REG_DA[(word2 >> 12) & 15]);
				if(CPU_TYPE_IS_020_VARIANT(CPU_TYPE))
					USE_CYCLES(2);
				return;
			}
			/* Memory to register */
			REG_DA[(word2 >> 12) & 15] = m68ki_read_32_fc(ea, REG_SFC);
			if(CPU_TYPE_IS_020_VARIANT(CPU_TYPE))
				USE_CYCLES(2);
			return;
		}
		m68ki_exception_privilege_violation();
		return;
	}
	m68ki_exception_illegal();
}