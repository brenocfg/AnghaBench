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

__attribute__((used)) static void tr_r0_to_PC(int const_val)
{
/*
 * do nothing - dispatcher will take care of this
	EOP_MOV_REG_LSL(1, 0, 16);		// mov  r1, r0, lsl #16
	EOP_STR_IMM(1,7,0x400+6*4);		// str  r1, [r7, #(0x400+6*8)]
	hostreg_r[1] = -1;
*/
}