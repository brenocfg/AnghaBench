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
 int /*<<< orphan*/  SSP_A ; 
 int /*<<< orphan*/  TR_WRITE_R0_TO_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ tr_predict_al_need () ; 

__attribute__((used)) static void tr_r0_to_A(int const_val)
{
	if (tr_predict_al_need()) {
		EOP_MOV_REG_LSL(5, 5, 16);	// mov  r5, r5, lsl #16
		EOP_MOV_REG_LSR(5, 5, 16);	// mov  r5, r5, lsr #16  @ AL
		EOP_ORR_REG_LSL(5, 5, 0, 16);	// orr  r5, r5, r0, lsl #16
	}
	else
		EOP_MOV_REG_LSL(5, 0, 16);
	TR_WRITE_R0_TO_REG(SSP_A);
}