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
struct task_struct {int dummy; } ;
struct stack_trace {scalar_t__ skip; unsigned long* entries; scalar_t__ nr_entries; scalar_t__ max_entries; } ;
struct pt_regs {unsigned long* regs; unsigned long cp0_epc; } ;

/* Variables and functions */
 unsigned long THREAD_SIZE ; 
 int /*<<< orphan*/  __kernel_text_address (unsigned long) ; 
 scalar_t__ raw_show_trace ; 
 int /*<<< orphan*/  save_raw_context_stack (struct stack_trace*,unsigned long) ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 
 unsigned long unwind_stack (struct task_struct*,unsigned long*,unsigned long,unsigned long*) ; 

__attribute__((used)) static void save_context_stack(struct stack_trace *trace,
	struct task_struct *tsk, struct pt_regs *regs)
{
	unsigned long sp = regs->regs[29];
#ifdef CONFIG_KALLSYMS
	unsigned long ra = regs->regs[31];
	unsigned long pc = regs->cp0_epc;

	if (raw_show_trace || !__kernel_text_address(pc)) {
		unsigned long stack_page =
			(unsigned long)task_stack_page(tsk);
		if (stack_page && sp >= stack_page &&
		    sp <= stack_page + THREAD_SIZE - 32)
			save_raw_context_stack(trace, sp);
		return;
	}
	do {
		if (trace->skip > 0)
			trace->skip--;
		else
			trace->entries[trace->nr_entries++] = pc;
		if (trace->nr_entries >= trace->max_entries)
			break;
		pc = unwind_stack(tsk, &sp, pc, &ra);
	} while (pc);
#else
	save_raw_context_stack(trace, sp);
#endif
}