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
 int CFLAG_SUB_32 (int,int,int) ; 
 scalar_t__ COND_CS () ; 
 int /*<<< orphan*/  CPU_TYPE ; 
 scalar_t__ CPU_TYPE_IS_EC020_PLUS (int /*<<< orphan*/ ) ; 
 int EA_AY_DI_32 () ; 
 int /*<<< orphan*/  EXCEPTION_CHK ; 
 int FLAG_C ; 
 int FLAG_Z ; 
 int OPER_I_16 () ; 
 int* REG_DA ; 
 int /*<<< orphan*/  m68ki_exception_illegal () ; 
 int /*<<< orphan*/  m68ki_exception_trap (int /*<<< orphan*/ ) ; 
 int m68ki_read_32 (int) ; 

void m68k_op_chk2cmp2_32_di(void)
{
	if(CPU_TYPE_IS_EC020_PLUS(CPU_TYPE))
	{
		uint word2 = OPER_I_16();
		uint compare = REG_DA[(word2 >> 12) & 15];
		uint ea = EA_AY_DI_32();
		uint lower_bound = m68ki_read_32(ea);
		uint upper_bound = m68ki_read_32(ea + 4);

		FLAG_C = compare - lower_bound;
		FLAG_Z = !((upper_bound==compare) | (lower_bound==compare));
		FLAG_C = CFLAG_SUB_32(lower_bound, compare, FLAG_C);
		if(COND_CS())
		{
			if(BIT_B(word2))
				m68ki_exception_trap(EXCEPTION_CHK);
			return;
		}

		FLAG_C = upper_bound - compare;
		FLAG_C = CFLAG_SUB_32(compare, upper_bound, FLAG_C);
		if(COND_CS() && BIT_B(word2))
				m68ki_exception_trap(EXCEPTION_CHK);
		return;
	}
	m68ki_exception_illegal();
}