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
struct task_struct {int /*<<< orphan*/  stack; int /*<<< orphan*/  dirties; } ;

/* Variables and functions */
 int /*<<< orphan*/  account_kernel_stack (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  free_thread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftrace_graph_exit_task (struct task_struct*) ; 
 int /*<<< orphan*/  prop_local_destroy_single (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_mutex_debug_task_free (struct task_struct*) ; 
 int /*<<< orphan*/  tracehook_free_task (struct task_struct*) ; 

void free_task(struct task_struct *tsk)
{
	prop_local_destroy_single(&tsk->dirties);
	account_kernel_stack(tsk->stack, -1);
	free_thread_info(tsk->stack);
	rt_mutex_debug_task_free(tsk);
	ftrace_graph_exit_task(tsk);
	tracehook_free_task(tsk);
	free_task_struct(tsk);
}