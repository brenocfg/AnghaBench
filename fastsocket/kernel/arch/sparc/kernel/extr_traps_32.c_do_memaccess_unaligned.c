#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int psr; scalar_t__ pc; int /*<<< orphan*/ * u_regs; } ;
struct TYPE_3__ {scalar_t__ si_trapno; void* si_addr; int /*<<< orphan*/  si_code; scalar_t__ si_errno; int /*<<< orphan*/  si_signo; } ;
typedef  TYPE_1__ siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADRALN ; 
 int PSR_PS ; 
 int /*<<< orphan*/  SIGBUS ; 
 size_t UREG_RETPC ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  die_if_kernel (char*,struct pt_regs*) ; 
 int /*<<< orphan*/  instruction_dump (unsigned long*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  send_sig_info (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 

void do_memaccess_unaligned(struct pt_regs *regs, unsigned long pc, unsigned long npc,
			    unsigned long psr)
{
	siginfo_t info;

	if(regs->psr & PSR_PS) {
		printk("KERNEL MNA at pc %08lx npc %08lx called by %08lx\n", pc, npc,
		       regs->u_regs[UREG_RETPC]);
		die_if_kernel("BOGUS", regs);
		/* die_if_kernel("Kernel MNA access", regs); */
	}
#if 0
	show_regs (regs);
	instruction_dump ((unsigned long *) regs->pc);
	printk ("do_MNA!\n");
#endif
	info.si_signo = SIGBUS;
	info.si_errno = 0;
	info.si_code = BUS_ADRALN;
	info.si_addr = /* FIXME: Should dig out mna address */ (void *)0;
	info.si_trapno = 0;
	send_sig_info(SIGBUS, &info, current);
}