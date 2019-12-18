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
struct TYPE_2__ {scalar_t__ sum_exec_runtime; } ;
struct task_struct {int /*<<< orphan*/ * sighand; struct signal_struct* signal; int /*<<< orphan*/  pending; TYPE_1__ se; int /*<<< orphan*/  ioac; scalar_t__ nivcsw; scalar_t__ nvcsw; scalar_t__ maj_flt; scalar_t__ min_flt; int /*<<< orphan*/  gtime; int /*<<< orphan*/  stime; int /*<<< orphan*/  utime; } ;
struct signal_struct {scalar_t__ notify_count; int /*<<< orphan*/  shared_pending; int /*<<< orphan*/  sum_sched_runtime; int /*<<< orphan*/  ioac; int /*<<< orphan*/  oublock; int /*<<< orphan*/  inblock; int /*<<< orphan*/  nivcsw; int /*<<< orphan*/  nvcsw; int /*<<< orphan*/  maj_flt; int /*<<< orphan*/  min_flt; void* gtime; void* stime; void* utime; struct task_struct* curr_target; scalar_t__ group_exit_task; int /*<<< orphan*/  count; } ;
struct sighand_struct {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  TIF_SIGPENDING ; 
 int /*<<< orphan*/  __cleanup_sighand (struct sighand_struct*) ; 
 int /*<<< orphan*/  __cleanup_signal (struct signal_struct*) ; 
 int /*<<< orphan*/  __unhash_process (struct task_struct*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 void* cputime_add (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_sigqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  has_group_leader_pid (struct task_struct*) ; 
 struct task_struct* next_thread (struct task_struct*) ; 
 int /*<<< orphan*/  posix_cpu_timers_exit (struct task_struct*) ; 
 int /*<<< orphan*/  posix_cpu_timers_exit_group (struct task_struct*) ; 
 struct sighand_struct* rcu_dereference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_io_accounting_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ task_io_get_inblock (struct task_struct*) ; 
 scalar_t__ task_io_get_oublock (struct task_struct*) ; 
 int /*<<< orphan*/  task_rq_unlock_wait (struct task_struct*) ; 
 int /*<<< orphan*/  taskstats_tgid_free (struct signal_struct*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 

__attribute__((used)) static void __exit_signal(struct task_struct *tsk)
{
	struct signal_struct *sig = tsk->signal;
	struct sighand_struct *sighand;

	BUG_ON(!sig);
	BUG_ON(!atomic_read(&sig->count));

	sighand = rcu_dereference(tsk->sighand);
	spin_lock(&sighand->siglock);

	posix_cpu_timers_exit(tsk);
	if (atomic_dec_and_test(&sig->count))
		posix_cpu_timers_exit_group(tsk);
	else {
		/*
		 * This can only happen if the caller is de_thread().
		 * FIXME: this is the temporary hack, we should teach
		 * posix-cpu-timers to handle this case correctly.
		 */
		if (unlikely(has_group_leader_pid(tsk)))
			posix_cpu_timers_exit_group(tsk);

		/*
		 * If there is any task waiting for the group exit
		 * then notify it:
		 */
		if (sig->group_exit_task && atomic_read(&sig->count) == sig->notify_count)
			wake_up_process(sig->group_exit_task);

		if (tsk == sig->curr_target)
			sig->curr_target = next_thread(tsk);
		/*
		 * Accumulate here the counters for all threads but the
		 * group leader as they die, so they can be added into
		 * the process-wide totals when those are taken.
		 * The group leader stays around as a zombie as long
		 * as there are other threads.  When it gets reaped,
		 * the exit.c code will add its counts into these totals.
		 * We won't ever get here for the group leader, since it
		 * will have been the last reference on the signal_struct.
		 */
		sig->utime = cputime_add(sig->utime, tsk->utime);
		sig->stime = cputime_add(sig->stime, tsk->stime);
		sig->gtime = cputime_add(sig->gtime, tsk->gtime);
		sig->min_flt += tsk->min_flt;
		sig->maj_flt += tsk->maj_flt;
		sig->nvcsw += tsk->nvcsw;
		sig->nivcsw += tsk->nivcsw;
		sig->inblock += task_io_get_inblock(tsk);
		sig->oublock += task_io_get_oublock(tsk);
		task_io_accounting_add(&sig->ioac, &tsk->ioac);
		sig->sum_sched_runtime += tsk->se.sum_exec_runtime;
		sig = NULL; /* Marker for below. */
	}

	__unhash_process(tsk);

	/*
	 * Do this under ->siglock, we can race with another thread
	 * doing sigqueue_free() if we have SIGQUEUE_PREALLOC signals.
	 */
	flush_sigqueue(&tsk->pending);

	tsk->signal = NULL;
	tsk->sighand = NULL;
	spin_unlock(&sighand->siglock);

	__cleanup_sighand(sighand);
	clear_tsk_thread_flag(tsk,TIF_SIGPENDING);
	if (sig) {
		flush_sigqueue(&sig->shared_pending);
		taskstats_tgid_free(sig);
		/*
		 * Make sure ->signal can't go away under rq->lock,
		 * see account_group_exec_runtime().
		 */
		task_rq_unlock_wait(tsk);
		__cleanup_signal(sig);
	}
}