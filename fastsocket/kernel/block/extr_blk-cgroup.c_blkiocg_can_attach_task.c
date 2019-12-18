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
struct task_struct {struct io_context* io_context; } ;
struct io_context {int /*<<< orphan*/  nr_tasks; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

__attribute__((used)) static int blkiocg_can_attach_task(struct cgroup *cgrp, struct task_struct *tsk)
{
	struct io_context *ioc;
	int ret = 0;

	/* task_lock() is needed to avoid races with exit_io_context() */
	task_lock(tsk);
	ioc = tsk->io_context;
	if (ioc && atomic_read(&ioc->nr_tasks) > 1)
		ret = -EINVAL;
	task_unlock(tsk);

	return ret;
}