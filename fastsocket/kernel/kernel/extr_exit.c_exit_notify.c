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
struct task_struct {scalar_t__ exit_signal; scalar_t__ parent_exec_id; scalar_t__ self_exec_id; TYPE_2__* signal; int /*<<< orphan*/  exit_state; TYPE_1__* real_parent; int /*<<< orphan*/  group_leader; } ;
struct TYPE_4__ {scalar_t__ notify_count; scalar_t__ group_exit_task; } ;
struct TYPE_3__ {scalar_t__ self_exec_id; } ;

/* Variables and functions */
 int DEATH_REAP ; 
 int /*<<< orphan*/  EXIT_DEAD ; 
 int /*<<< orphan*/  EXIT_ZOMBIE ; 
 scalar_t__ SIGCHLD ; 
 int do_notify_parent (struct task_struct*,int) ; 
 int /*<<< orphan*/  exit_task_namespaces (struct task_struct*) ; 
 int /*<<< orphan*/  forget_original_parent (struct task_struct*) ; 
 int /*<<< orphan*/  kill_orphaned_pgrp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_task (struct task_struct*) ; 
 int /*<<< orphan*/  task_detached (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ thread_group_leader (struct task_struct*) ; 
 int tracehook_notify_death (struct task_struct*,void**,int) ; 
 int /*<<< orphan*/  tracehook_report_death (struct task_struct*,int,void*,int) ; 
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void exit_notify(struct task_struct *tsk, int group_dead)
{
	int signal;
	void *cookie;

	/*
	 * This does two things:
	 *
  	 * A.  Make init inherit all the child processes
	 * B.  Check to see if any process groups have become orphaned
	 *	as a result of our exiting, and if they have any stopped
	 *	jobs, send them a SIGHUP and then a SIGCONT.  (POSIX 3.2.2.2)
	 */
	forget_original_parent(tsk);
	exit_task_namespaces(tsk);

	write_lock_irq(&tasklist_lock);
	if (group_dead)
		kill_orphaned_pgrp(tsk->group_leader, NULL);

	/* Let father know we died
	 *
	 * Thread signals are configurable, but you aren't going to use
	 * that to send signals to arbitary processes.
	 * That stops right now.
	 *
	 * If the parent exec id doesn't match the exec id we saved
	 * when we started then we know the parent has changed security
	 * domain.
	 *
	 * If our self_exec id doesn't match our parent_exec_id then
	 * we have changed execution domain as these two values started
	 * the same after a fork.
	 */
	if (tsk->exit_signal != SIGCHLD && !task_detached(tsk) &&
	    (tsk->parent_exec_id != tsk->real_parent->self_exec_id ||
	     tsk->self_exec_id != tsk->parent_exec_id))
		tsk->exit_signal = SIGCHLD;

	signal = tracehook_notify_death(tsk, &cookie, group_dead);
	if (signal >= 0)
		signal = do_notify_parent(tsk, signal);

	tsk->exit_state = signal == DEATH_REAP ? EXIT_DEAD : EXIT_ZOMBIE;

	/* mt-exec, de_thread() is waiting for us */
	if (thread_group_leader(tsk) &&
	    tsk->signal->group_exit_task &&
	    tsk->signal->notify_count < 0)
		wake_up_process(tsk->signal->group_exit_task);

	write_unlock_irq(&tasklist_lock);

	tracehook_report_death(tsk, signal, cookie, group_dead);

	/* If the process is dead, release it - nobody will wait for it */
	if (signal == DEATH_REAP)
		release_task(tsk);
}