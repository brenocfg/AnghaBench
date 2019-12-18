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
struct pt_regs {int dummy; } ;
struct TYPE_3__ {unsigned long si_errno; int /*<<< orphan*/  si_code; scalar_t__ si_imm; int /*<<< orphan*/ * si_addr; scalar_t__ si_isr; scalar_t__ si_flags; int /*<<< orphan*/  si_signo; } ;
typedef  TYPE_1__ siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  TRAP_BRKPT ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ die_if_kernel (char*,struct pt_regs*,unsigned long) ; 
 int /*<<< orphan*/  force_sig_info (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

void
ia32_bad_interrupt (unsigned long int_num, struct pt_regs *regs)
{
	siginfo_t siginfo;

	if (die_if_kernel("Bad IA-32 interrupt", regs, int_num))
		return;

	siginfo.si_signo = SIGTRAP;
	siginfo.si_errno = int_num;	/* XXX is it OK to abuse si_errno like this? */
	siginfo.si_flags = 0;
	siginfo.si_isr = 0;
	siginfo.si_addr = NULL;
	siginfo.si_imm = 0;
	siginfo.si_code = TRAP_BRKPT;
	force_sig_info(SIGTRAP, &siginfo, current);
}