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
struct task_struct {scalar_t__ exit_state; struct sighand_struct* sighand; int /*<<< orphan*/  exit_signal; struct task_struct* group_leader; int /*<<< orphan*/  tasks; int /*<<< orphan*/  pid; int /*<<< orphan*/  start_time; struct signal_struct* signal; } ;
struct signal_struct {int notify_count; int /*<<< orphan*/  maxrss; struct task_struct* group_exit_task; int /*<<< orphan*/  count; } ;
struct sighand_struct {int /*<<< orphan*/  siglock; int /*<<< orphan*/  action; int /*<<< orphan*/  count; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_2__ {scalar_t__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int ENOMEM ; 
 scalar_t__ EXIT_DEAD ; 
 scalar_t__ EXIT_ZOMBIE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PIDTYPE_PGID ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int /*<<< orphan*/  PIDTYPE_SID ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __cleanup_sighand (struct sighand_struct*) ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  attach_pid (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  detach_pid (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_itimers (struct signal_struct*) ; 
 int /*<<< orphan*/  flush_itimer_signals () ; 
 int has_group_leader_pid (struct task_struct*) ; 
 struct sighand_struct* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (scalar_t__) ; 
 int /*<<< orphan*/  list_replace_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct sighand_struct*,struct sighand_struct*) ; 
 int /*<<< orphan*/  release_task (struct task_struct*) ; 
 int /*<<< orphan*/  same_thread_group (struct task_struct*,struct task_struct*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  setmax_mm_hiwater_rss (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sighand_cachep ; 
 scalar_t__ signal_group_exit (struct signal_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ thread_group_empty (struct task_struct*) ; 
 scalar_t__ thread_group_leader (struct task_struct*) ; 
 int /*<<< orphan*/  transfer_pid (struct task_struct*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_other_threads (struct task_struct*) ; 

__attribute__((used)) static int de_thread(struct task_struct *tsk)
{
	struct signal_struct *sig = tsk->signal;
	struct sighand_struct *oldsighand = tsk->sighand;
	spinlock_t *lock = &oldsighand->siglock;
	int count;

	if (thread_group_empty(tsk))
		goto no_thread_group;

	/*
	 * Kill all other threads in the thread group.
	 */
	spin_lock_irq(lock);
	if (signal_group_exit(sig)) {
		/*
		 * Another group action in progress, just
		 * return so that the signal is processed.
		 */
		spin_unlock_irq(lock);
		return -EAGAIN;
	}
	sig->group_exit_task = tsk;
	zap_other_threads(tsk);

	/* Account for the thread group leader hanging around: */
	count = thread_group_leader(tsk) ? 1 : 2;
	sig->notify_count = count;
	while (atomic_read(&sig->count) > count) {
		__set_current_state(TASK_UNINTERRUPTIBLE);
		spin_unlock_irq(lock);
		schedule();
		spin_lock_irq(lock);
	}
	spin_unlock_irq(lock);

	/*
	 * At this point all other threads have exited, all we have to
	 * do is to wait for the thread group leader to become inactive,
	 * and to assume its PID:
	 */
	if (!thread_group_leader(tsk)) {
		struct task_struct *leader = tsk->group_leader;

		sig->notify_count = -1;	/* for exit_notify() */
		for (;;) {
			write_lock_irq(&tasklist_lock);
			if (likely(leader->exit_state))
				break;
			__set_current_state(TASK_UNINTERRUPTIBLE);
			write_unlock_irq(&tasklist_lock);
			schedule();
		}

		/*
		 * The only record we have of the real-time age of a
		 * process, regardless of execs it's done, is start_time.
		 * All the past CPU time is accumulated in signal_struct
		 * from sister threads now dead.  But in this non-leader
		 * exec, nothing survives from the original leader thread,
		 * whose birth marks the true age of this process now.
		 * When we take on its identity by switching to its PID, we
		 * also take its birthdate (always earlier than our own).
		 */
		tsk->start_time = leader->start_time;

		BUG_ON(!same_thread_group(leader, tsk));
		BUG_ON(has_group_leader_pid(tsk));
		/*
		 * An exec() starts a new thread group with the
		 * TGID of the previous thread group. Rehash the
		 * two threads with a switched PID, and release
		 * the former thread group leader:
		 */

		/* Become a process group leader with the old leader's pid.
		 * The old leader becomes a thread of the this thread group.
		 * Note: The old leader also uses this pid until release_task
		 *       is called.  Odd but simple and correct.
		 */
		detach_pid(tsk, PIDTYPE_PID);
		tsk->pid = leader->pid;
		attach_pid(tsk, PIDTYPE_PID,  task_pid(leader));
		transfer_pid(leader, tsk, PIDTYPE_PGID);
		transfer_pid(leader, tsk, PIDTYPE_SID);
		list_replace_rcu(&leader->tasks, &tsk->tasks);

		tsk->group_leader = tsk;
		leader->group_leader = tsk;

		tsk->exit_signal = SIGCHLD;

		BUG_ON(leader->exit_state != EXIT_ZOMBIE);
		leader->exit_state = EXIT_DEAD;
		write_unlock_irq(&tasklist_lock);

		release_task(leader);
	}

	sig->group_exit_task = NULL;
	sig->notify_count = 0;

no_thread_group:
	if (current->mm)
		setmax_mm_hiwater_rss(&sig->maxrss, current->mm);

	exit_itimers(sig);
	flush_itimer_signals();

	if (atomic_read(&oldsighand->count) != 1) {
		struct sighand_struct *newsighand;
		/*
		 * This ->sighand is shared with the CLONE_SIGHAND
		 * but not CLONE_THREAD task, switch to the new one.
		 */
		newsighand = kmem_cache_alloc(sighand_cachep, GFP_KERNEL);
		if (!newsighand)
			return -ENOMEM;

		atomic_set(&newsighand->count, 1);
		memcpy(newsighand->action, oldsighand->action,
		       sizeof(newsighand->action));

		write_lock_irq(&tasklist_lock);
		spin_lock(&oldsighand->siglock);
		rcu_assign_pointer(tsk->sighand, newsighand);
		spin_unlock(&oldsighand->siglock);
		write_unlock_irq(&tasklist_lock);

		__cleanup_sighand(oldsighand);
	}

	BUG_ON(!thread_group_leader(tsk));
	return 0;
}