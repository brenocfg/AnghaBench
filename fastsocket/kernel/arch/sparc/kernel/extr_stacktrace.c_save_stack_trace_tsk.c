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
struct thread_info {int dummy; } ;
struct task_struct {int dummy; } ;
struct stack_trace {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __save_stack_trace (struct thread_info*,struct stack_trace*,int) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 

void save_stack_trace_tsk(struct task_struct *tsk, struct stack_trace *trace)
{
	struct thread_info *tp = task_thread_info(tsk);

	__save_stack_trace(tp, trace, true);
}