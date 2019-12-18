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

/* Variables and functions */
 int /*<<< orphan*/  CFLAG_CLEAR ; 
 int DX ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int /*<<< orphan*/  FLAG_Z ; 
 int /*<<< orphan*/  MASK_OUT_ABOVE_16 (int) ; 
 int /*<<< orphan*/  NFLAG_16 (int /*<<< orphan*/ ) ; 
 int OPER_AY_IX_16 () ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 

void m68k_op_and_16_er_ix(void)
{
	FLAG_Z = MASK_OUT_ABOVE_16(DX &= (OPER_AY_IX_16() | 0xffff0000));

	FLAG_N = NFLAG_16(FLAG_Z);
	FLAG_C = CFLAG_CLEAR;
	FLAG_V = VFLAG_CLEAR;
}