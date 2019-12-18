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
 scalar_t__* gr_info ; 
 int /*<<< orphan*/  set_rse_reg (struct kvm_pt_regs*,unsigned long,unsigned long,int) ; 

void setreg(unsigned long regnum, unsigned long val,
			int nat, struct kvm_pt_regs *regs)
{
	unsigned long addr;
	unsigned long bitmask;
	unsigned long *unat;

	/*
	 * First takes care of stacked registers
	 */
	if (regnum >= IA64_FIRST_STACKED_GR) {
		set_rse_reg(regs, regnum, val, nat);
		return;
	}

	/*
	 * Now look at registers in [0-31] range and init correct UNAT
	 */
	addr = (unsigned long)regs;
	unat = &regs->eml_unat;
	/*
	 * add offset from base of struct
	 * and do it !
	 */
	addr += gr_info[regnum];

	*(unsigned long *)addr = val;

	/*
	 * We need to clear the corresponding UNAT bit to fully emulate the load
	 * UNAT bit_pos = GR[r3]{8:3} form EAS-2.4
	 */
	bitmask   = 1UL << ((addr >> 3) & 0x3f);
	if (nat)
		*unat |= bitmask;
	 else
		*unat &= ~bitmask;

}