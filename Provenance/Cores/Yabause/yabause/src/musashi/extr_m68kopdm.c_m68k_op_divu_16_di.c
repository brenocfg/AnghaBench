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
 int /*<<< orphan*/  CFLAG_CLEAR ; 
 int DX ; 
 int /*<<< orphan*/  EXCEPTION_ZERO_DIVIDE ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int FLAG_Z ; 
 int MASK_OUT_ABOVE_16 (int) ; 
 int MASK_OUT_ABOVE_32 (int) ; 
 int /*<<< orphan*/  NFLAG_16 (int) ; 
 int OPER_AY_DI_16 () ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 
 int /*<<< orphan*/  VFLAG_SET ; 
 int /*<<< orphan*/  m68ki_exception_trap (int /*<<< orphan*/ ) ; 

void m68k_op_divu_16_di(void)
{
	uint* r_dst = &DX;
	uint src = OPER_AY_DI_16();

	if(src != 0)
	{
		uint quotient = *r_dst / src;
		uint remainder = *r_dst % src;

		if(quotient < 0x10000)
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