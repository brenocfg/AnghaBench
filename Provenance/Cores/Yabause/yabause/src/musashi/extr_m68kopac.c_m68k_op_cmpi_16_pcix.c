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
typedef  scalar_t__ uint ;

/* Variables and functions */
 int /*<<< orphan*/  CFLAG_16 (scalar_t__) ; 
 int /*<<< orphan*/  CPU_TYPE ; 
 scalar_t__ CPU_TYPE_IS_EC020_PLUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int /*<<< orphan*/  FLAG_Z ; 
 int /*<<< orphan*/  MASK_OUT_ABOVE_16 (scalar_t__) ; 
 int /*<<< orphan*/  NFLAG_16 (scalar_t__) ; 
 scalar_t__ OPER_I_16 () ; 
 scalar_t__ OPER_PCIX_16 () ; 
 int /*<<< orphan*/  VFLAG_SUB_16 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  m68ki_exception_illegal () ; 

void m68k_op_cmpi_16_pcix(void)
{
	if(CPU_TYPE_IS_EC020_PLUS(CPU_TYPE))
	{
		uint src = OPER_I_16();
		uint dst = OPER_PCIX_16();
		uint res = dst - src;

		FLAG_N = NFLAG_16(res);
		FLAG_Z = MASK_OUT_ABOVE_16(res);
		FLAG_V = VFLAG_SUB_16(src, dst, res);
		FLAG_C = CFLAG_16(res);
		return;
	}
	m68ki_exception_illegal();
}