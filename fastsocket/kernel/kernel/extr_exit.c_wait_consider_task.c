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
struct wait_opts {int notask_error; } ;
struct task_struct {scalar_t__ exit_state; } ;

/* Variables and functions */
 scalar_t__ EXIT_DEAD ; 
 scalar_t__ EXIT_ZOMBIE ; 
 int /*<<< orphan*/  delay_group_leader (struct task_struct*) ; 
 int eligible_child (struct wait_opts*,struct task_struct*) ; 
 scalar_t__ likely (int) ; 
 int security_task_wait (struct task_struct*) ; 
 int task_ptrace (struct task_struct*) ; 
 scalar_t__ task_stopped_code (struct task_struct*,int) ; 
 scalar_t__ unlikely (int) ; 
 int wait_task_continued (struct wait_opts*,struct task_struct*) ; 
 int wait_task_stopped (struct wait_opts*,int,struct task_struct*) ; 
 int wait_task_zombie (struct wait_opts*,struct task_struct*) ; 

__attribute__((used)) static int wait_consider_task(struct wait_opts *wo, int ptrace,
				struct task_struct *p)
{
	int ret = eligible_child(wo, p);
	if (!ret)
		return ret;

	ret = security_task_wait(p);
	if (unlikely(ret < 0)) {
		/*
		 * If we have not yet seen any eligible child,
		 * then let this error code replace -ECHILD.
		 * A permission error will give the user a clue
		 * to look for security policy problems, rather
		 * than for mysterious wait bugs.
		 */
		if (wo->notask_error)
			wo->notask_error = ret;
		return 0;
	}

	if (likely(!ptrace) && unlikely(task_ptrace(p))) {
		/*
		 * This child is hidden by ptrace.
		 * We aren't allowed to see it now, but eventually we will.
		 */
		wo->notask_error = 0;
		return 0;
	}

	if (p->exit_state == EXIT_DEAD)
		return 0;

	/*
	 * We don't reap group leaders with subthreads.
	 */
	if (p->exit_state == EXIT_ZOMBIE && !delay_group_leader(p))
		return wait_task_zombie(wo, p);

	/*
	 * It's stopped or running now, so it might
	 * later continue, exit, or stop again.
	 */
	wo->notask_error = 0;

	if (task_stopped_code(p, ptrace))
		return wait_task_stopped(wo, ptrace, p);

	return wait_task_continued(wo, p);
}