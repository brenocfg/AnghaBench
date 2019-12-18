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
 int /*<<< orphan*/  EOP_MOV_REG_LSL (int,int,int) ; 
 int /*<<< orphan*/  EOP_MOV_REG_LSR (int,int,int) ; 
 int /*<<< orphan*/  EOP_ORR_REG_LSL (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KRREG_P ; 
 int /*<<< orphan*/  SSP_X ; 
 int /*<<< orphan*/  TR_WRITE_R0_TO_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dirty_regb ; 

__attribute__((used)) static void tr_r0_to_X(int const_val)
{
	EOP_MOV_REG_LSL(4, 4, 16);		// mov  r4, r4, lsl #16
	EOP_MOV_REG_LSR(4, 4, 16);		// mov  r4, r4, lsr #16
	EOP_ORR_REG_LSL(4, 4, 0, 16);		// orr  r4, r4, r0, lsl #16
	dirty_regb |= KRREG_P;			// touching X or Y makes P dirty.
	TR_WRITE_R0_TO_REG(SSP_X);
}