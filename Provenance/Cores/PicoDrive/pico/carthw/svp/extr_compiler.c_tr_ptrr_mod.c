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
struct TYPE_4__ {int* r; TYPE_1__* gr; } ;
struct TYPE_3__ {int h; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_COND_AL ; 
 int /*<<< orphan*/  A_COND_EQ ; 
 int /*<<< orphan*/  A_OP_ADD ; 
 int /*<<< orphan*/  A_OP_AND ; 
 int /*<<< orphan*/  A_OP_MOV ; 
 int /*<<< orphan*/  A_OP_SUB ; 
 int /*<<< orphan*/  EOP_ADD_IMM (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EOP_ADD_REG2_LSL (int,int,int,int) ; 
 int /*<<< orphan*/  EOP_AND_IMM (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EOP_C_DOP_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  EOP_MOV_IMM (int,int,int) ; 
 int /*<<< orphan*/  EOP_MOV_REG2_ROR (int,int,int) ; 
 int /*<<< orphan*/  EOP_MOV_REG_LSR (int,int,int) ; 
 int /*<<< orphan*/  EOP_MOV_REG_ROR (int,int,int) ; 
 int /*<<< orphan*/  EOP_RSB_IMM (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EOP_SUB_IMM (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EOP_SUB_REG2_LSL (int,int,int,int) ; 
 int KRREG_ST ; 
 size_t SSP_ST ; 
 int dirty_regb ; 
 int* hostreg_r ; 
 int known_regb ; 
 TYPE_2__ known_regs ; 
 int /*<<< orphan*/  tr_release_pr (int) ; 

__attribute__((used)) static void tr_ptrr_mod(int r, int mod, int need_modulo, int count)
{
	int modulo_shift = -1;	/* unknown */

	if (mod == 0) return;

	if (!need_modulo || mod == 1) // +!
		modulo_shift = 8;
	else if (need_modulo && (known_regb & KRREG_ST)) {
		modulo_shift = known_regs.gr[SSP_ST].h & 7;
		if (modulo_shift == 0) modulo_shift = 8;
	}

	if (modulo_shift == -1)
	{
		int reg = (r < 4) ? 8 : 9;
		tr_release_pr(r);
		if (dirty_regb & KRREG_ST) {
			// avoid flushing ARM flags
			EOP_AND_IMM(1, 6, 0, 0x70);
			EOP_SUB_IMM(1, 1, 0, 0x10);
			EOP_AND_IMM(1, 1, 0, 0x70);
			EOP_ADD_IMM(1, 1, 0, 0x10);
		} else {
			EOP_C_DOP_IMM(A_COND_AL,A_OP_AND,1,6,1,0,0x70);	// ands  r1, r6, #0x70
			EOP_C_DOP_IMM(A_COND_EQ,A_OP_MOV,0,0,1,0,0x80); // moveq r1, #0x80
		}
		EOP_MOV_REG_LSR(1, 1, 4);		// mov r1, r1, lsr #4
		EOP_RSB_IMM(2, 1, 0, 8);		// rsb r1, r1, #8
		EOP_MOV_IMM(3, 8/2, count);		// mov r3, #0x01000000
		if (r&3)
			EOP_ADD_IMM(1, 1, 0, (r&3)*8);	// add r1, r1, #(r&3)*8
		EOP_MOV_REG2_ROR(reg,reg,1);		// mov reg, reg, ror r1
		if (mod == 2)
		     EOP_SUB_REG2_LSL(reg,reg,3,2);	// sub reg, reg, #0x01000000 << r2
		else EOP_ADD_REG2_LSL(reg,reg,3,2);
		EOP_RSB_IMM(1, 1, 0, 32);		// rsb r1, r1, #32
		EOP_MOV_REG2_ROR(reg,reg,1);		// mov reg, reg, ror r1
		hostreg_r[1] = hostreg_r[2] = hostreg_r[3] = -1;
	}
	else if (known_regb & (1 << (r + 8)))
	{
		int modulo = (1 << modulo_shift) - 1;
		if (mod == 2)
		     known_regs.r[r] = (known_regs.r[r] & ~modulo) | ((known_regs.r[r] - count) & modulo);
		else known_regs.r[r] = (known_regs.r[r] & ~modulo) | ((known_regs.r[r] + count) & modulo);
	}
	else
	{
		int reg = (r < 4) ? 8 : 9;
		int ror = ((r&3) + 1)*8 - (8 - modulo_shift);
		EOP_MOV_REG_ROR(reg,reg,ror);
		// {add|sub} reg, reg, #1<<shift
		EOP_C_DOP_IMM(A_COND_AL,(mod==2)?A_OP_SUB:A_OP_ADD,0,reg,reg, 8/2, count << (8 - modulo_shift));
		EOP_MOV_REG_ROR(reg,reg,32-ror);
	}
}