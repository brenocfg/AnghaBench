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
 int /*<<< orphan*/  CPU_TYPE ; 
 scalar_t__ CPU_TYPE_IS_EC020_PLUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EA_A7_PD_8 () ; 
 int EA_AY_PD_8 () ; 
 int OPER_I_16 () ; 
 int /*<<< orphan*/  m68ki_exception_illegal () ; 
 int m68ki_read_8 (int) ; 
 int /*<<< orphan*/  m68ki_write_8 (int /*<<< orphan*/ ,int) ; 

void m68k_op_pack_16_mm_ax7(void)
{
	if(CPU_TYPE_IS_EC020_PLUS(CPU_TYPE))
	{
		/* Note: AX and AY are reversed in Motorola's docs */
		uint ea_src = EA_AY_PD_8();
		uint src = m68ki_read_8(ea_src);
		ea_src = EA_AY_PD_8();
		src = ((src << 8) | m68ki_read_8(ea_src)) + OPER_I_16();

		m68ki_write_8(EA_A7_PD_8(), ((src >> 4) & 0x00f0) | (src & 0x000f));
		return;
	}
	m68ki_exception_illegal();
}