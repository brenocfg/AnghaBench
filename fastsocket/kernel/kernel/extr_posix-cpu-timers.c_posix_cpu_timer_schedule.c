#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union cpu_time_count {int dummy; } cpu_time_count ;
struct task_struct {int /*<<< orphan*/  exit_state; int /*<<< orphan*/ * signal; } ;
struct TYPE_4__ {scalar_t__ sched; } ;
struct TYPE_5__ {TYPE_1__ expires; struct task_struct* task; } ;
struct TYPE_6__ {TYPE_2__ cpu; } ;
struct k_itimer {int it_overrun_last; int it_overrun; int /*<<< orphan*/  it_requeue_pending; int /*<<< orphan*/  it_clock; TYPE_3__ it; } ;

/* Variables and functions */
 scalar_t__ CPUCLOCK_PERTHREAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_timer (struct k_itimer*,union cpu_time_count) ; 
 int /*<<< orphan*/  bump_cpu_timer (struct k_itimer*,union cpu_time_count) ; 
 int /*<<< orphan*/  clear_dead_task (struct k_itimer*,union cpu_time_count) ; 
 int /*<<< orphan*/  cpu_clock_sample (int /*<<< orphan*/ ,struct task_struct*,union cpu_time_count*) ; 
 int /*<<< orphan*/  cpu_timer_sample_group (int /*<<< orphan*/ ,struct task_struct*,union cpu_time_count*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ thread_group_empty (struct task_struct*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void posix_cpu_timer_schedule(struct k_itimer *timer)
{
	struct task_struct *p = timer->it.cpu.task;
	union cpu_time_count now;

	if (unlikely(p == NULL))
		/*
		 * The task was cleaned up already, no future firings.
		 */
		goto out;

	/*
	 * Fetch the current sample and update the timer's expiry time.
	 */
	if (CPUCLOCK_PERTHREAD(timer->it_clock)) {
		cpu_clock_sample(timer->it_clock, p, &now);
		bump_cpu_timer(timer, now);
		if (unlikely(p->exit_state)) {
			clear_dead_task(timer, now);
			goto out;
		}
		read_lock(&tasklist_lock); /* arm_timer needs it.  */
	} else {
		read_lock(&tasklist_lock);
		if (unlikely(p->signal == NULL)) {
			/*
			 * The process has been reaped.
			 * We can't even collect a sample any more.
			 */
			put_task_struct(p);
			timer->it.cpu.task = p = NULL;
			timer->it.cpu.expires.sched = 0;
			goto out_unlock;
		} else if (unlikely(p->exit_state) && thread_group_empty(p)) {
			/*
			 * We've noticed that the thread is dead, but
			 * not yet reaped.  Take this opportunity to
			 * drop our task ref.
			 */
			clear_dead_task(timer, now);
			goto out_unlock;
		}
		cpu_timer_sample_group(timer->it_clock, p, &now);
		bump_cpu_timer(timer, now);
		/* Leave the tasklist_lock locked for the call below.  */
	}

	/*
	 * Now re-arm for the new expiry time.
	 */
	arm_timer(timer, now);

out_unlock:
	read_unlock(&tasklist_lock);

out:
	timer->it_overrun_last = timer->it_overrun;
	timer->it_overrun = -1;
	++timer->it_requeue_pending;
}