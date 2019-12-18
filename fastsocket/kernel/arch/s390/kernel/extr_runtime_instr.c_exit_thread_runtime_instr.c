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
struct TYPE_2__ {int /*<<< orphan*/ * ri_cb; scalar_t__ ri_signum; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 struct task_struct* current ; 
 int /*<<< orphan*/  disable_runtime_instr () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void exit_thread_runtime_instr(void)
{
	struct task_struct *task = current;

	if (!task->thread.ri_cb)
		return;
	disable_runtime_instr();
	kfree(task->thread.ri_cb);
	task->thread.ri_signum = 0;
	task->thread.ri_cb = NULL;
}