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
struct stack_frame {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  backtrace_ops ; 
 int /*<<< orphan*/  dump_trace (int /*<<< orphan*/ *,struct pt_regs* const,unsigned long*,int /*<<< orphan*/ *,unsigned int*) ; 
 struct stack_frame* dump_user_backtrace (struct stack_frame*) ; 
 scalar_t__ frame_pointer (struct pt_regs* const) ; 
 unsigned long kernel_stack_pointer (struct pt_regs* const) ; 
 int /*<<< orphan*/  user_mode_vm (struct pt_regs* const) ; 
 scalar_t__ x86_backtrace_32 (struct pt_regs* const,unsigned int) ; 

void
x86_backtrace(struct pt_regs * const regs, unsigned int depth)
{
	struct stack_frame *head = (struct stack_frame *)frame_pointer(regs);

	if (!user_mode_vm(regs)) {
		unsigned long stack = kernel_stack_pointer(regs);
		if (depth)
			dump_trace(NULL, regs, (unsigned long *)stack,
				   &backtrace_ops, &depth);
		return;
	}

	if (x86_backtrace_32(regs, depth))
		return;

	while (depth-- && head)
		head = dump_user_backtrace(head);
}