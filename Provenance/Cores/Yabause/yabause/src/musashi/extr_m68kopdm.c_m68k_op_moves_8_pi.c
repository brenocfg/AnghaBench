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
 scalar_t__ BIT_F (int) ; 
 int /*<<< orphan*/  CPU_TYPE ; 
 scalar_t__ CPU_TYPE_IS_010_PLUS (int /*<<< orphan*/ ) ; 
 scalar_t__ CPU_TYPE_IS_020_VARIANT (int /*<<< orphan*/ ) ; 
 int EA_AY_PI_8 () ; 
 scalar_t__ FLAG_S ; 
 int /*<<< orphan*/  MAKE_INT_8 (int) ; 
 int /*<<< orphan*/  MASK_OUT_ABOVE_8 (int /*<<< orphan*/ ) ; 
 int MASK_OUT_BELOW_8 (int) ; 
 int OPER_I_16 () ; 
 int /*<<< orphan*/ * REG_A ; 
 int* REG_D ; 
 int /*<<< orphan*/ * REG_DA ; 
 int /*<<< orphan*/  REG_DFC ; 
 int /*<<< orphan*/  REG_SFC ; 
 int /*<<< orphan*/  USE_CYCLES (int) ; 
 int /*<<< orphan*/  m68ki_exception_illegal () ; 
 int /*<<< orphan*/  m68ki_exception_privilege_violation () ; 
 int m68ki_read_8_fc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m68ki_trace_t0 () ; 
 int /*<<< orphan*/  m68ki_write_8_fc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void m68k_op_moves_8_pi(void)
{
	if(CPU_TYPE_IS_010_PLUS(CPU_TYPE))
	{
		if(FLAG_S)
		{
			uint word2 = OPER_I_16();
			uint ea = EA_AY_PI_8();

			m68ki_trace_t0();			   /* auto-disable (see m68kcpu.h) */
			if(BIT_B(word2))		   /* Register to memory */
			{
				m68ki_write_8_fc(ea, REG_DFC, MASK_OUT_ABOVE_8(REG_DA[(word2 >> 12) & 15]));
				return;
			}
			if(BIT_F(word2))		   /* Memory to address register */
			{
				REG_A[(word2 >> 12) & 7] = MAKE_INT_8(m68ki_read_8_fc(ea, REG_SFC));
				if(CPU_TYPE_IS_020_VARIANT(CPU_TYPE))
					USE_CYCLES(2);
				return;
			}
			/* Memory to data register */
			REG_D[(word2 >> 12) & 7] = MASK_OUT_BELOW_8(REG_D[(word2 >> 12) & 7]) | m68ki_read_8_fc(ea, REG_SFC);
			if(CPU_TYPE_IS_020_VARIANT(CPU_TYPE))
				USE_CYCLES(2);
			return;
		}
		m68ki_exception_privilege_violation();
		return;
	}
	m68ki_exception_illegal();
}