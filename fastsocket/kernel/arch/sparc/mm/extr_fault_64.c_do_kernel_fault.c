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
struct pt_regs {int tstate; int /*<<< orphan*/  tpc; scalar_t__ tnpc; } ;
struct exception_table_entry {int /*<<< orphan*/  fixup; } ;

/* Variables and functions */
 unsigned char ASI_P ; 
 int FAULT_CODE_ITLB ; 
 int FAULT_CODE_WRITE ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int TSTATE_PRIV ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  do_fault_siginfo (int,int /*<<< orphan*/ ,struct pt_regs*,unsigned int,int) ; 
 int /*<<< orphan*/  handle_ld_nf (unsigned int,struct pt_regs*) ; 
 int /*<<< orphan*/  handle_ldf_stq (unsigned int,struct pt_regs*) ; 
 struct exception_table_entry* search_exception_tables (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unhandled_fault (unsigned long,int /*<<< orphan*/ ,struct pt_regs*) ; 

__attribute__((used)) static void do_kernel_fault(struct pt_regs *regs, int si_code, int fault_code,
			    unsigned int insn, unsigned long address)
{
	unsigned char asi = ASI_P;
 
	if ((!insn) && (regs->tstate & TSTATE_PRIV))
		goto cannot_handle;

	/* If user insn could be read (thus insn is zero), that
	 * is fine.  We will just gun down the process with a signal
	 * in that case.
	 */

	if (!(fault_code & (FAULT_CODE_WRITE|FAULT_CODE_ITLB)) &&
	    (insn & 0xc0800000) == 0xc0800000) {
		if (insn & 0x2000)
			asi = (regs->tstate >> 24);
		else
			asi = (insn >> 5);
		if ((asi & 0xf2) == 0x82) {
			if (insn & 0x1000000) {
				handle_ldf_stq(insn, regs);
			} else {
				/* This was a non-faulting load. Just clear the
				 * destination register(s) and continue with the next
				 * instruction. -jj
				 */
				handle_ld_nf(insn, regs);
			}
			return;
		}
	}
		
	/* Is this in ex_table? */
	if (regs->tstate & TSTATE_PRIV) {
		const struct exception_table_entry *entry;

		entry = search_exception_tables(regs->tpc);
		if (entry) {
			regs->tpc = entry->fixup;
			regs->tnpc = regs->tpc + 4;
			return;
		}
	} else {
		/* The si_code was set to make clear whether
		 * this was a SEGV_MAPERR or SEGV_ACCERR fault.
		 */
		do_fault_siginfo(si_code, SIGSEGV, regs, insn, fault_code);
		return;
	}

cannot_handle:
	unhandled_fault (address, current, regs);
}