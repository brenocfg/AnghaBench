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
struct TYPE_2__ {unsigned long ksp; } ;
struct task_struct {TYPE_1__ thread; } ;
struct stack_trace {scalar_t__ nr_entries; scalar_t__ max_entries; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */
 unsigned long PSW_ADDR_INSN ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  save_context_stack (struct stack_trace*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ task_pt_regs (struct task_struct*) ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 

void save_stack_trace_tsk(struct task_struct *tsk, struct stack_trace *trace)
{
	unsigned long sp, low, high;

	sp = tsk->thread.ksp & PSW_ADDR_INSN;
	low = (unsigned long) task_stack_page(tsk);
	high = (unsigned long) task_pt_regs(tsk);
	save_context_stack(trace, sp, low, high, 0);
	if (trace->nr_entries < trace->max_entries)
		trace->entries[trace->nr_entries++] = ULONG_MAX;
}