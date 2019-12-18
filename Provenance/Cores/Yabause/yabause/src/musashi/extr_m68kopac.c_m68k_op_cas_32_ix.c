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
 int /*<<< orphan*/  CFLAG_SUB_32 (int,int,int) ; 
 scalar_t__ COND_NE () ; 
 int /*<<< orphan*/  CPU_TYPE ; 
 scalar_t__ CPU_TYPE_IS_EC020_PLUS (int /*<<< orphan*/ ) ; 
 int EA_AY_IX_32 () ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int /*<<< orphan*/  FLAG_Z ; 
 int /*<<< orphan*/  MASK_OUT_ABOVE_32 (int) ; 
 int /*<<< orphan*/  NFLAG_32 (int) ; 
 int OPER_I_16 () ; 
 int* REG_D ; 
 int /*<<< orphan*/  USE_CYCLES (int) ; 
 int /*<<< orphan*/  VFLAG_SUB_32 (int,int,int) ; 
 int /*<<< orphan*/  m68ki_exception_illegal () ; 
 int m68ki_read_32 (int) ; 
 int /*<<< orphan*/  m68ki_trace_t0 () ; 
 int /*<<< orphan*/  m68ki_write_32 (int,int) ; 

void m68k_op_cas_32_ix(void)
{
	if(CPU_TYPE_IS_EC020_PLUS(CPU_TYPE))
	{
		uint word2 = OPER_I_16();
		uint ea = EA_AY_IX_32();
		uint dest = m68ki_read_32(ea);
		uint* compare = &REG_D[word2 & 7];
		uint res = dest - *compare;

		m68ki_trace_t0();			   /* auto-disable (see m68kcpu.h) */
		FLAG_N = NFLAG_32(res);
		FLAG_Z = MASK_OUT_ABOVE_32(res);
		FLAG_V = VFLAG_SUB_32(*compare, dest, res);
		FLAG_C = CFLAG_SUB_32(*compare, dest, res);

		if(COND_NE())
			*compare = dest;
		else
		{
			USE_CYCLES(3);
			m68ki_write_32(ea, REG_D[(word2 >> 6) & 7]);
		}
		return;
	}
	m68ki_exception_illegal();
}