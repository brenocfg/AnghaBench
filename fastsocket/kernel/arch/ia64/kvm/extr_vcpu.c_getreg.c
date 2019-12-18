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
struct kvm_pt_regs {unsigned long eml_unat; } ;

/* Variables and functions */
 unsigned long IA64_FIRST_STACKED_GR ; 
 int /*<<< orphan*/  get_rse_reg (struct kvm_pt_regs*,unsigned long,unsigned long*,int*) ; 
 scalar_t__* gr_info ; 

void getreg(unsigned long regnum, unsigned long *val,
				int *nat, struct kvm_pt_regs *regs)
{
	unsigned long addr, *unat;
	if (regnum >= IA64_FIRST_STACKED_GR) {
		get_rse_reg(regs, regnum, val, nat);
		return;
	}

	/*
	 * Now look at registers in [0-31] range and init correct UNAT
	 */
	addr = (unsigned long)regs;
	unat = &regs->eml_unat;

	addr += gr_info[regnum];

	*val  = *(unsigned long *)addr;
	/*
	 * do it only when requested
	 */
	if (nat)
		*nat  = (*unat >> ((addr >> 3) & 0x3f)) & 0x1UL;
}