#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* gr; } ;
struct TYPE_3__ {int l; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOP_MOV_REG_LSR (int,int,int) ; 
 int /*<<< orphan*/  EOP_MOV_REG_ROR (int,int,int) ; 
 int /*<<< orphan*/  EOP_ORR_REG_LSL (int,int,int /*<<< orphan*/ ,int) ; 
 size_t SSP_A ; 
 int SSP_AL ; 
 int /*<<< orphan*/  hostreg_sspreg_changed (int) ; 
 int known_regb ; 
 TYPE_2__ known_regs ; 

__attribute__((used)) static void tr_r0_to_AL(int const_val)
{
	EOP_MOV_REG_LSR(5, 5, 16);		// mov  r5, r5, lsr #16
	EOP_ORR_REG_LSL(5, 5, 0, 16);		// orr  r5, r5, r0, lsl #16
	EOP_MOV_REG_ROR(5, 5, 16);		// mov  r5, r5, ror #16
	hostreg_sspreg_changed(SSP_AL);
	if (const_val != -1) {
		known_regs.gr[SSP_A].l = const_val;
		known_regb |= 1 << SSP_AL;
	} else
		known_regb &= ~(1 << SSP_AL);
}