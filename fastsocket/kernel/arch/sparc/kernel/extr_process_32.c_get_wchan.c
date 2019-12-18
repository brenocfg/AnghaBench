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
struct thread_info {int dummy; } ;
struct task_struct {scalar_t__ state; } ;
struct reg_window32 {unsigned long* ins; } ;
struct TYPE_2__ {unsigned long ksp; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 scalar_t__ TASK_RUNNING ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  in_sched_functions (unsigned long) ; 
 TYPE_1__* task_thread_info (struct task_struct*) ; 

unsigned long get_wchan(struct task_struct *task)
{
	unsigned long pc, fp, bias = 0;
	unsigned long task_base = (unsigned long) task;
        unsigned long ret = 0;
	struct reg_window32 *rw;
	int count = 0;

	if (!task || task == current ||
            task->state == TASK_RUNNING)
		goto out;

	fp = task_thread_info(task)->ksp + bias;
	do {
		/* Bogus frame pointer? */
		if (fp < (task_base + sizeof(struct thread_info)) ||
		    fp >= (task_base + (2 * PAGE_SIZE)))
			break;
		rw = (struct reg_window32 *) fp;
		pc = rw->ins[7];
		if (!in_sched_functions(pc)) {
			ret = pc;
			goto out;
		}
		fp = rw->ins[6] + bias;
	} while (++count < 16);

out:
	return ret;
}