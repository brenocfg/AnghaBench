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
struct TYPE_2__ {int /*<<< orphan*/  ksp; } ;
struct task_struct {TYPE_1__ thread; } ;
struct stack_trace {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  save_context_stack (struct stack_trace*,int /*<<< orphan*/ ,struct task_struct*,int /*<<< orphan*/ ) ; 

void save_stack_trace_tsk(struct task_struct *tsk, struct stack_trace *trace)
{
	save_context_stack(trace, tsk->thread.ksp, tsk, 0);
}