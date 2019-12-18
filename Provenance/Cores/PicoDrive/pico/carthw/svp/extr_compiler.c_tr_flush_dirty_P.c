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
 int /*<<< orphan*/  EOP_MOV_REG_ASR (int,int,int) ; 
 int /*<<< orphan*/  EOP_MOV_REG_LSL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  EOP_MUL (int,int /*<<< orphan*/ ,int) ; 
 int KRREG_P ; 
 int dirty_regb ; 
 int* hostreg_r ; 

__attribute__((used)) static void tr_flush_dirty_P(void)
{
	// TODO: const regs
	if (!(dirty_regb & KRREG_P)) return;
	EOP_MOV_REG_ASR(10, 4, 16);		// mov  r10, r4, asr #16
	EOP_MOV_REG_LSL( 0, 4, 16);		// mov  r0,  r4, lsl #16
	EOP_MOV_REG_ASR( 0, 0, 15);		// mov  r0,  r0, asr #15
	EOP_MUL(10, 0, 10);			// mul  r10, r0, r10
	dirty_regb &= ~KRREG_P;
	hostreg_r[0] = -1;
}