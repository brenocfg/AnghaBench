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
struct task_struct {scalar_t__ exit_state; int /*<<< orphan*/  rcu; int /*<<< orphan*/  exit_signal; struct task_struct* group_leader; } ;
struct TYPE_4__ {TYPE_1__* user; } ;
struct TYPE_3__ {int /*<<< orphan*/  processes; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EXIT_DEAD ; 
 scalar_t__ EXIT_ZOMBIE ; 
 int /*<<< orphan*/  __exit_signal (struct task_struct*) ; 
 TYPE_2__* __task_cred (struct task_struct*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delayed_put_task_struct ; 
 int /*<<< orphan*/  do_notify_parent (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_flush_task (struct task_struct*) ; 
 int /*<<< orphan*/  release_thread (struct task_struct*) ; 
 int task_detached (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ thread_group_empty (struct task_struct*) ; 
 int /*<<< orphan*/  tracehook_finish_release_task (struct task_struct*) ; 
 int /*<<< orphan*/  tracehook_prepare_release_task (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

void release_task(struct task_struct * p)
{
	struct task_struct *leader;
	int zap_leader;
repeat:
	tracehook_prepare_release_task(p);
	/* don't need to get the RCU readlock here - the process is dead and
	 * can't be modifying its own credentials */
	atomic_dec(&__task_cred(p)->user->processes);

	proc_flush_task(p);

	write_lock_irq(&tasklist_lock);
	tracehook_finish_release_task(p);
	__exit_signal(p);

	/*
	 * If we are the last non-leader member of the thread
	 * group, and the leader is zombie, then notify the
	 * group leader's parent process. (if it wants notification.)
	 */
	zap_leader = 0;
	leader = p->group_leader;
	if (leader != p && thread_group_empty(leader) && leader->exit_state == EXIT_ZOMBIE) {
		BUG_ON(task_detached(leader));
		do_notify_parent(leader, leader->exit_signal);
		/*
		 * If we were the last child thread and the leader has
		 * exited already, and the leader's parent ignores SIGCHLD,
		 * then we are the one who should release the leader.
		 *
		 * do_notify_parent() will have marked it self-reaping in
		 * that case.
		 */
		zap_leader = task_detached(leader);

		/*
		 * This maintains the invariant that release_task()
		 * only runs on a task in EXIT_DEAD, just for sanity.
		 */
		if (zap_leader)
			leader->exit_state = EXIT_DEAD;
	}

	write_unlock_irq(&tasklist_lock);
	release_thread(p);
	call_rcu(&p->rcu, delayed_put_task_struct);

	p = leader;
	if (unlikely(zap_leader))
		goto repeat;
}