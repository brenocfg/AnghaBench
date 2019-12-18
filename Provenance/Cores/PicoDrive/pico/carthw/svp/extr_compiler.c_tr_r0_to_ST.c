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
 int /*<<< orphan*/  EOP_AND_IMM (int,int,int,int) ; 
 int /*<<< orphan*/  EOP_ORR_REG_LSL (int,int,int,int) ; 
 int /*<<< orphan*/  KRREG_ST ; 
 int /*<<< orphan*/  SSP_ST ; 
 int /*<<< orphan*/  TR_WRITE_R0_TO_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dirty_regb ; 
 int* hostreg_r ; 

__attribute__((used)) static void tr_r0_to_ST(int const_val)
{
	// VR doesn't need much accuracy here..
	EOP_AND_IMM(1, 0,   0, 0x67);		// and   r1, r0, #0x67
	EOP_AND_IMM(6, 6, 8/2, 0xe0);		// and   r6, r6, #7<<29     @ preserve STACK
	EOP_ORR_REG_LSL(6, 6, 1, 4);		// orr   r6, r6, r1, lsl #4
	TR_WRITE_R0_TO_REG(SSP_ST);
	hostreg_r[1] = -1;
	dirty_regb &= ~KRREG_ST;
}