#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int single_step; int ss_nextcnt; int insn1_type; unsigned int addr1; short insn1; int insn2_type; unsigned int addr2; short insn2; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {unsigned int cp0_epc; unsigned int* regs; } ;

/* Variables and functions */
 unsigned long B16 ; 
 unsigned long B16M ; 
 unsigned long B32 ; 
 unsigned long B32M ; 
 unsigned long BR16 ; 
 unsigned long BR16M ; 
 unsigned long BR32 ; 
 unsigned long BR32M ; 
 unsigned long J16 ; 
 unsigned long J16M ; 
 unsigned long J32 ; 
 unsigned long J32M ; 
 int /*<<< orphan*/  SINGLESTEP16_INSN ; 
 int /*<<< orphan*/  SINGLESTEP32_INSN ; 
 scalar_t__ is_16bitinsn (unsigned long) ; 
 int /*<<< orphan*/  read_tsk_long (struct task_struct*,unsigned int,unsigned long*) ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 int /*<<< orphan*/  write_tsk_long (struct task_struct*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_tsk_short (struct task_struct*,unsigned int,int /*<<< orphan*/ ) ; 

void user_enable_single_step(struct task_struct *child)
{
	/* far_epc is the target of branch */
	unsigned int epc, far_epc = 0;
	unsigned long epc_insn, far_epc_insn;
	int ninsn_type;			/* next insn type 0=16b, 1=32b */
	unsigned int tmp, tmp2;
	struct pt_regs *regs = task_pt_regs(child);
	child->thread.single_step = 1;
	child->thread.ss_nextcnt = 1;
	epc = regs->cp0_epc;

	read_tsk_long(child, epc, &epc_insn);

	if (is_16bitinsn(epc_insn)) {
		if ((epc_insn & J16M) == J16) {
			tmp = epc_insn & 0xFFE;
			epc = (epc & 0xFFFFF000) | tmp;
		} else if ((epc_insn & B16M) == B16) {
			child->thread.ss_nextcnt = 2;
			tmp = (epc_insn & 0xFF) << 1;
			tmp = tmp << 23;
			tmp = (unsigned int)((int) tmp >> 23);
			far_epc = epc + tmp;
			epc += 2;
		} else if ((epc_insn & BR16M) == BR16) {
			child->thread.ss_nextcnt = 2;
			tmp = (epc_insn >> 4) & 0xF;
			far_epc = regs->regs[tmp];
			epc += 2;
		} else
			epc += 2;
	} else {
		if ((epc_insn & J32M) == J32) {
			tmp = epc_insn & 0x03FFFFFE;
			tmp2 = tmp & 0x7FFF;
			tmp = (((tmp >> 16) & 0x3FF) << 15) | tmp2;
			epc = (epc & 0xFFC00000) | tmp;
		} else if ((epc_insn & B32M) == B32) {
			child->thread.ss_nextcnt = 2;
			tmp = epc_insn & 0x03FFFFFE;	/* discard LK bit */
			tmp2 = tmp & 0x3FF;
			tmp = (((tmp >> 16) & 0x3FF) << 10) | tmp2; /* 20bit */
			tmp = tmp << 12;
			tmp = (unsigned int)((int) tmp >> 12);
			far_epc = epc + tmp;
			epc += 4;
		} else if ((epc_insn & BR32M) == BR32) {
			child->thread.ss_nextcnt = 2;
			tmp = (epc_insn >> 16) & 0x1F;
			far_epc = regs->regs[tmp];
			epc += 4;
		} else
			epc += 4;
	}

	if (child->thread.ss_nextcnt == 1) {
		read_tsk_long(child, epc, &epc_insn);

		if (is_16bitinsn(epc_insn)) {
			write_tsk_short(child, epc, SINGLESTEP16_INSN);
			ninsn_type = 0;
		} else {
			write_tsk_long(child, epc, SINGLESTEP32_INSN);
			ninsn_type = 1;
		}

		if (ninsn_type == 0) {  /* 16bits */
			child->thread.insn1_type = 0;
			child->thread.addr1 = epc;
			 /* the insn may have 32bit data */
			child->thread.insn1 = (short)epc_insn;
		} else {
			child->thread.insn1_type = 1;
			child->thread.addr1 = epc;
			child->thread.insn1 = epc_insn;
		}
	} else {
		/* branch! have two target child->thread.ss_nextcnt=2 */
		read_tsk_long(child, epc, &epc_insn);
		read_tsk_long(child, far_epc, &far_epc_insn);
		if (is_16bitinsn(epc_insn)) {
			write_tsk_short(child, epc, SINGLESTEP16_INSN);
			ninsn_type = 0;
		} else {
			write_tsk_long(child, epc, SINGLESTEP32_INSN);
			ninsn_type = 1;
		}

		if (ninsn_type == 0) {  /* 16bits */
			child->thread.insn1_type = 0;
			child->thread.addr1 = epc;
			 /* the insn may have 32bit data */
			child->thread.insn1 = (short)epc_insn;
		} else {
			child->thread.insn1_type = 1;
			child->thread.addr1 = epc;
			child->thread.insn1 = epc_insn;
		}

		if (is_16bitinsn(far_epc_insn)) {
			write_tsk_short(child, far_epc, SINGLESTEP16_INSN);
			ninsn_type = 0;
		} else {
			write_tsk_long(child, far_epc, SINGLESTEP32_INSN);
			ninsn_type = 1;
		}

		if (ninsn_type == 0) {  /* 16bits */
			child->thread.insn2_type = 0;
			child->thread.addr2 = far_epc;
			 /* the insn may have 32bit data */
			child->thread.insn2 = (short)far_epc_insn;
		} else {
			child->thread.insn2_type = 1;
			child->thread.addr2 = far_epc;
			child->thread.insn2 = far_epc_insn;
		}
	}
}