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
 scalar_t__ CPU_TYPE_IS_010_PLUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPU_TYPE_IS_EC020_PLUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAG_M ; 
 scalar_t__ FLAG_S ; 
 int OPER_I_16 () ; 
 int /*<<< orphan*/  REG_CAAR ; 
 int /*<<< orphan*/  REG_CACR ; 
 int /*<<< orphan*/ * REG_DA ; 
 int /*<<< orphan*/  REG_DFC ; 
 int /*<<< orphan*/  REG_ISP ; 
 int /*<<< orphan*/  REG_MSP ; 
 int /*<<< orphan*/  REG_SFC ; 
 int /*<<< orphan*/  REG_SP ; 
 int /*<<< orphan*/  REG_USP ; 
 int /*<<< orphan*/  REG_VBR ; 
 int /*<<< orphan*/  m68ki_exception_illegal () ; 
 int /*<<< orphan*/  m68ki_exception_privilege_violation () ; 
 int /*<<< orphan*/  m68ki_trace_t0 () ; 

void m68k_op_movec_32_cr(void)
{
	if(CPU_TYPE_IS_010_PLUS(CPU_TYPE))
	{
		if(FLAG_S)
		{
			uint word2 = OPER_I_16();

			m68ki_trace_t0();		   /* auto-disable (see m68kcpu.h) */
			switch (word2 & 0xfff)
			{
			case 0x000:			   /* SFC */
				REG_DA[(word2 >> 12) & 15] = REG_SFC;
				return;
			case 0x001:			   /* DFC */
				REG_DA[(word2 >> 12) & 15] = REG_DFC;
				return;
			case 0x002:			   /* CACR */
				if(CPU_TYPE_IS_EC020_PLUS(CPU_TYPE))
				{
					REG_DA[(word2 >> 12) & 15] = REG_CACR;
					return;
				}
				return;
			case 0x800:			   /* USP */
				REG_DA[(word2 >> 12) & 15] = REG_USP;
				return;
			case 0x801:			   /* VBR */
				REG_DA[(word2 >> 12) & 15] = REG_VBR;
				return;
			case 0x802:			   /* CAAR */
				if(CPU_TYPE_IS_EC020_PLUS(CPU_TYPE))
				{
					REG_DA[(word2 >> 12) & 15] = REG_CAAR;
					return;
				}
				m68ki_exception_illegal();
				break;
			case 0x803:			   /* MSP */
				if(CPU_TYPE_IS_EC020_PLUS(CPU_TYPE))
				{
					REG_DA[(word2 >> 12) & 15] = FLAG_M ? REG_SP : REG_MSP;
					return;
				}
				m68ki_exception_illegal();
				return;
			case 0x804:			   /* ISP */
				if(CPU_TYPE_IS_EC020_PLUS(CPU_TYPE))
				{
					REG_DA[(word2 >> 12) & 15] = FLAG_M ? REG_ISP : REG_SP;
					return;
				}
				m68ki_exception_illegal();
				return;
			default:
				m68ki_exception_illegal();
				return;
			}
		}
		m68ki_exception_privilege_violation();
		return;
	}
	m68ki_exception_illegal();
}