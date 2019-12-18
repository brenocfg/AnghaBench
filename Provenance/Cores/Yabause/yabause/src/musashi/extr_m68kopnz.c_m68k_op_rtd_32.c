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
typedef  int /*<<< orphan*/  uint ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TYPE ; 
 scalar_t__ CPU_TYPE_IS_010_PLUS (int /*<<< orphan*/ ) ; 
 scalar_t__ MAKE_INT_16 (int /*<<< orphan*/ ) ; 
 scalar_t__ MASK_OUT_ABOVE_32 (scalar_t__) ; 
 int /*<<< orphan*/  OPER_I_16 () ; 
 scalar_t__* REG_A ; 
 int /*<<< orphan*/  m68ki_exception_illegal () ; 
 int /*<<< orphan*/  m68ki_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m68ki_pull_32 () ; 
 int /*<<< orphan*/  m68ki_trace_t0 () ; 

void m68k_op_rtd_32(void)
{
	if(CPU_TYPE_IS_010_PLUS(CPU_TYPE))
	{
		uint new_pc = m68ki_pull_32();

		m68ki_trace_t0();			   /* auto-disable (see m68kcpu.h) */
		REG_A[7] = MASK_OUT_ABOVE_32(REG_A[7] + MAKE_INT_16(OPER_I_16()));
		m68ki_jump(new_pc);
		return;
	}
	m68ki_exception_illegal();
}