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
struct pt_regs {int bpc; } ;

/* Variables and functions */
 int emu_m32r2 (unsigned short,struct pt_regs*) ; 

__attribute__((used)) static int insn_check(unsigned long insn, struct pt_regs *regs,
	unsigned char **ucp)
{
	int res = 0;

	/*
	 * 32bit insn
	 *  ld Rdest, @(disp16, Rsrc)
	 *  st Rdest, @(disp16, Rsrc)
	 */
	if (insn & 0x80000000) {	/* 32bit insn */
		*ucp += (short)(insn & 0x0000ffff);
		regs->bpc += 4;
	} else {			/* 16bit insn */
#ifdef CONFIG_ISA_DUAL_ISSUE
		/* parallel exec check */
		if (!(regs->bpc & 0x2) && insn & 0x8000) {
			res = emu_m32r2((unsigned short)insn, regs);
			regs->bpc += 4;
		} else
#endif	/* CONFIG_ISA_DUAL_ISSUE */
			regs->bpc += 2;
	}

	return res;
}