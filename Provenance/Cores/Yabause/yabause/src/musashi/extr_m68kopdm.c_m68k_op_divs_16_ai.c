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
typedef  int uint32 ;
typedef  scalar_t__ uint ;
typedef  int sint ;

/* Variables and functions */
 int /*<<< orphan*/  CFLAG_CLEAR ; 
 scalar_t__ DX ; 
 int /*<<< orphan*/  EXCEPTION_ZERO_DIVIDE ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int FLAG_Z ; 
 int MAKE_INT_16 (int) ; 
 int MAKE_INT_32 (scalar_t__) ; 
 int MASK_OUT_ABOVE_16 (int) ; 
 scalar_t__ MASK_OUT_ABOVE_32 (int) ; 
 int /*<<< orphan*/  NFLAG_16 (int) ; 
 int /*<<< orphan*/  NFLAG_CLEAR ; 
 int OPER_AY_AI_16 () ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 
 int /*<<< orphan*/  VFLAG_SET ; 
 int /*<<< orphan*/  m68ki_exception_trap (int /*<<< orphan*/ ) ; 

void m68k_op_divs_16_ai(void)
{
	uint* r_dst = &DX;
	sint src = MAKE_INT_16(OPER_AY_AI_16());
	sint quotient;
	sint remainder;

	if(src != 0)
	{
		if((uint32)*r_dst == 0x80000000 && src == -1)
		{
			FLAG_Z = 0;
			FLAG_N = NFLAG_CLEAR;
			FLAG_V = VFLAG_CLEAR;
			FLAG_C = CFLAG_CLEAR;
			*r_dst = 0;
			return;
		}

		quotient = MAKE_INT_32(*r_dst) / src;
		remainder = MAKE_INT_32(*r_dst) % src;

		if(quotient == MAKE_INT_16(quotient))
		{
			FLAG_Z = quotient;
			FLAG_N = NFLAG_16(quotient);
			FLAG_V = VFLAG_CLEAR;
			FLAG_C = CFLAG_CLEAR;
			*r_dst = MASK_OUT_ABOVE_32(MASK_OUT_ABOVE_16(quotient) | (remainder << 16));
			return;
		}
		FLAG_V = VFLAG_SET;
		return;
	}
	m68ki_exception_trap(EXCEPTION_ZERO_DIVIDE);
}