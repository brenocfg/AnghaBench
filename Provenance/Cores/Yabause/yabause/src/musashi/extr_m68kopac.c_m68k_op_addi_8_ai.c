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
 int /*<<< orphan*/  CFLAG_8 (scalar_t__) ; 
 scalar_t__ EA_AY_AI_8 () ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int /*<<< orphan*/  FLAG_X ; 
 int /*<<< orphan*/  FLAG_Z ; 
 int /*<<< orphan*/  MASK_OUT_ABOVE_8 (scalar_t__) ; 
 int /*<<< orphan*/  NFLAG_8 (scalar_t__) ; 
 scalar_t__ OPER_I_8 () ; 
 int /*<<< orphan*/  VFLAG_ADD_8 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ m68ki_read_8 (scalar_t__) ; 
 int /*<<< orphan*/  m68ki_write_8 (scalar_t__,int /*<<< orphan*/ ) ; 

void m68k_op_addi_8_ai(void)
{
	uint src = OPER_I_8();
	uint ea = EA_AY_AI_8();
	uint dst = m68ki_read_8(ea);
	uint res = src + dst;

	FLAG_N = NFLAG_8(res);
	FLAG_V = VFLAG_ADD_8(src, dst, res);
	FLAG_X = FLAG_C = CFLAG_8(res);
	FLAG_Z = MASK_OUT_ABOVE_8(res);

	m68ki_write_8(ea, FLAG_Z);
}