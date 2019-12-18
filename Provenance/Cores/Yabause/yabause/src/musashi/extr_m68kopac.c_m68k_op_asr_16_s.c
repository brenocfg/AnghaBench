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
typedef  size_t uint ;

/* Variables and functions */
 size_t DY ; 
 size_t FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 size_t FLAG_X ; 
 size_t FLAG_Z ; 
 scalar_t__ GET_MSB_16 (size_t) ; 
 size_t MASK_OUT_ABOVE_16 (size_t) ; 
 size_t MASK_OUT_BELOW_16 (size_t) ; 
 int /*<<< orphan*/  NFLAG_16 (size_t) ; 
 int REG_IR ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 
 size_t* m68ki_shift_16_table ; 

void m68k_op_asr_16_s(void)
{
	uint* r_dst = &DY;
	uint shift = (((REG_IR >> 9) - 1) & 7) + 1;
	uint src = MASK_OUT_ABOVE_16(*r_dst);
	uint res = src >> shift;

	if(GET_MSB_16(src))
		res |= m68ki_shift_16_table[shift];

	*r_dst = MASK_OUT_BELOW_16(*r_dst) | res;

	FLAG_N = NFLAG_16(res);
	FLAG_Z = res;
	FLAG_V = VFLAG_CLEAR;
	FLAG_X = FLAG_C = src << (9-shift);
}