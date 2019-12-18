#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread_info {int dummy; } ;
struct TYPE_3__ {unsigned long ksp; } ;
struct TYPE_4__ {TYPE_1__ cpu_context; } ;
struct task_struct {TYPE_2__ thread; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 scalar_t__ THREAD_SIZE ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  dump_mem (char*,char const*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  show_trace_log_lvl (struct task_struct*,unsigned long*,struct pt_regs*,char const*) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 
 scalar_t__ valid_stack_ptr (struct thread_info*,unsigned long) ; 

void show_stack_log_lvl(struct task_struct *tsk, unsigned long sp,
			struct pt_regs *regs, const char *log_lvl)
{
	struct thread_info *tinfo;

	if (sp == 0) {
		if (tsk)
			sp = tsk->thread.cpu_context.ksp;
		else
			sp = (unsigned long)&tinfo;
	}
	if (!tsk)
		tsk = current;

	tinfo = task_thread_info(tsk);

	if (valid_stack_ptr(tinfo, sp)) {
		dump_mem("Stack: ", log_lvl, sp,
			 THREAD_SIZE + (unsigned long)tinfo);
		show_trace_log_lvl(tsk, (unsigned long *)sp, regs, log_lvl);
	}
}