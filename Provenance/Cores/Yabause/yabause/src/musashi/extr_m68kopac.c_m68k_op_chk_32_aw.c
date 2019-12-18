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
typedef  scalar_t__ sint ;

/* Variables and functions */
 int /*<<< orphan*/  CFLAG_CLEAR ; 
 int /*<<< orphan*/  CPU_TYPE ; 
 scalar_t__ CPU_TYPE_IS_EC020_PLUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DX ; 
 int /*<<< orphan*/  EXCEPTION_CHK ; 
 int /*<<< orphan*/  FLAG_C ; 
 int FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int /*<<< orphan*/  FLAG_Z ; 
 scalar_t__ MAKE_INT_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPER_AW_32 () ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 
 int /*<<< orphan*/  ZFLAG_32 (scalar_t__) ; 
 int /*<<< orphan*/  m68ki_exception_illegal () ; 
 int /*<<< orphan*/  m68ki_exception_trap (int /*<<< orphan*/ ) ; 

void m68k_op_chk_32_aw(void)
{
	if(CPU_TYPE_IS_EC020_PLUS(CPU_TYPE))
	{
		sint src = MAKE_INT_32(DX);
		sint bound = MAKE_INT_32(OPER_AW_32());

		FLAG_Z = ZFLAG_32(src); /* Undocumented */
		FLAG_V = VFLAG_CLEAR;   /* Undocumented */
		FLAG_C = CFLAG_CLEAR;   /* Undocumented */

		if(src >= 0 && src <= bound)
		{
			return;
		}
		FLAG_N = (src < 0)<<7;
		m68ki_exception_trap(EXCEPTION_CHK);
		return;
	}
	m68ki_exception_illegal();
}