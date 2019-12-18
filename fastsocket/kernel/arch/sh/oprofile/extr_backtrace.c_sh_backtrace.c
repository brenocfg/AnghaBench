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
struct pt_regs {scalar_t__* regs; } ;

/* Variables and functions */
 unsigned int backtrace_limit ; 
 int /*<<< orphan*/  backtrace_ops ; 
 int /*<<< orphan*/  unwind_stack (int /*<<< orphan*/ *,struct pt_regs* const,unsigned long*,int /*<<< orphan*/ *,unsigned int*) ; 
 unsigned long* user_backtrace (unsigned long*,struct pt_regs* const) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs* const) ; 

void sh_backtrace(struct pt_regs * const regs, unsigned int depth)
{
	unsigned long *stackaddr;

	/*
	 * Paranoia - clip max depth as we could get lost in the weeds.
	 */
	if (depth > backtrace_limit)
		depth = backtrace_limit;

	stackaddr = (unsigned long *)regs->regs[15];
	if (!user_mode(regs)) {
		if (depth)
			unwind_stack(NULL, regs, stackaddr,
				     &backtrace_ops, &depth);
		return;
	}

	while (depth-- && (stackaddr != NULL))
		stackaddr = user_backtrace(stackaddr, regs);
}