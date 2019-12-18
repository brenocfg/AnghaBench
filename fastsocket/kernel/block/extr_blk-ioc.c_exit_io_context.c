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
struct task_struct {struct io_context* io_context; } ;
struct io_context {TYPE_1__* aic; int /*<<< orphan*/  nr_tasks; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* exit ) (TYPE_1__*) ;} ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfq_exit (struct io_context*) ; 
 int /*<<< orphan*/  put_io_context (struct io_context*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

void exit_io_context(struct task_struct *task)
{
	struct io_context *ioc;

	task_lock(task);
	ioc = task->io_context;
	task->io_context = NULL;
	task_unlock(task);

	if (atomic_dec_and_test(&ioc->nr_tasks)) {
		if (ioc->aic && ioc->aic->exit)
			ioc->aic->exit(ioc->aic);
		cfq_exit(ioc);

	}
	put_io_context(ioc);
}