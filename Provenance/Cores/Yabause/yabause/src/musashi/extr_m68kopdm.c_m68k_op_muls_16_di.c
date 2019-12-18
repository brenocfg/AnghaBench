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
 int /*<<< orphan*/  CFLAG_CLEAR ; 
 int /*<<< orphan*/  DX ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int /*<<< orphan*/  FLAG_Z ; 
 int MAKE_INT_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASK_OUT_ABOVE_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASK_OUT_ABOVE_32 (int) ; 
 int /*<<< orphan*/  NFLAG_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPER_AY_DI_16 () ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 

void m68k_op_muls_16_di(void)
{
	uint* r_dst = &DX;
	uint res = MASK_OUT_ABOVE_32(MAKE_INT_16(OPER_AY_DI_16()) * MAKE_INT_16(MASK_OUT_ABOVE_16(*r_dst)));

	*r_dst = res;

	FLAG_Z = res;
	FLAG_N = NFLAG_32(res);
	FLAG_V = VFLAG_CLEAR;
	FLAG_C = CFLAG_CLEAR;
}