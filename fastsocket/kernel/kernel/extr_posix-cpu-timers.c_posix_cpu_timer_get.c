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
union cpu_time_count {scalar_t__ sched; } ;
struct task_struct {int exit_state; int /*<<< orphan*/ * signal; } ;
struct TYPE_4__ {union cpu_time_count expires; union cpu_time_count incr; struct task_struct* task; } ;
struct TYPE_5__ {TYPE_1__ cpu; } ;
struct k_itimer {int it_sigev_notify; TYPE_2__ it; int /*<<< orphan*/  it_clock; } ;
struct TYPE_6__ {int tv_sec; int tv_nsec; } ;
struct itimerspec {TYPE_3__ it_value; TYPE_3__ it_interval; } ;

/* Variables and functions */
 scalar_t__ CPUCLOCK_PERTHREAD (int /*<<< orphan*/ ) ; 
 int SIGEV_NONE ; 
 int SIGEV_THREAD_ID ; 
 int /*<<< orphan*/  bump_cpu_timer (struct k_itimer*,union cpu_time_count) ; 
 int /*<<< orphan*/  clear_dead_task (struct k_itimer*,union cpu_time_count) ; 
 int /*<<< orphan*/  cpu_clock_sample (int /*<<< orphan*/ ,struct task_struct*,union cpu_time_count*) ; 
 scalar_t__ cpu_time_before (int /*<<< orphan*/ ,union cpu_time_count,union cpu_time_count) ; 
 union cpu_time_count cpu_time_sub (int /*<<< orphan*/ ,union cpu_time_count,union cpu_time_count) ; 
 int /*<<< orphan*/  cpu_timer_sample_group (int /*<<< orphan*/ ,struct task_struct*,union cpu_time_count*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sample_to_timespec (int /*<<< orphan*/ ,union cpu_time_count,TYPE_3__*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ thread_group_empty (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void posix_cpu_timer_get(struct k_itimer *timer, struct itimerspec *itp)
{
	union cpu_time_count now;
	struct task_struct *p = timer->it.cpu.task;
	int clear_dead;

	/*
	 * Easy part: convert the reload time.
	 */
	sample_to_timespec(timer->it_clock,
			   timer->it.cpu.incr, &itp->it_interval);

	if (timer->it.cpu.expires.sched == 0) {	/* Timer not armed at all.  */
		itp->it_value.tv_sec = itp->it_value.tv_nsec = 0;
		return;
	}

	if (unlikely(p == NULL)) {
		/*
		 * This task already died and the timer will never fire.
		 * In this case, expires is actually the dead value.
		 */
	dead:
		sample_to_timespec(timer->it_clock, timer->it.cpu.expires,
				   &itp->it_value);
		return;
	}

	/*
	 * Sample the clock to take the difference with the expiry time.
	 */
	if (CPUCLOCK_PERTHREAD(timer->it_clock)) {
		cpu_clock_sample(timer->it_clock, p, &now);
		clear_dead = p->exit_state;
	} else {
		read_lock(&tasklist_lock);
		if (unlikely(p->signal == NULL)) {
			/*
			 * The process has been reaped.
			 * We can't even collect a sample any more.
			 * Call the timer disarmed, nothing else to do.
			 */
			put_task_struct(p);
			timer->it.cpu.task = NULL;
			timer->it.cpu.expires.sched = 0;
			read_unlock(&tasklist_lock);
			goto dead;
		} else {
			cpu_timer_sample_group(timer->it_clock, p, &now);
			clear_dead = (unlikely(p->exit_state) &&
				      thread_group_empty(p));
		}
		read_unlock(&tasklist_lock);
	}

	if ((timer->it_sigev_notify & ~SIGEV_THREAD_ID) == SIGEV_NONE) {
		if (timer->it.cpu.incr.sched == 0 &&
		    cpu_time_before(timer->it_clock,
				    timer->it.cpu.expires, now)) {
			/*
			 * Do-nothing timer expired and has no reload,
			 * so it's as if it was never set.
			 */
			timer->it.cpu.expires.sched = 0;
			itp->it_value.tv_sec = itp->it_value.tv_nsec = 0;
			return;
		}
		/*
		 * Account for any expirations and reloads that should
		 * have happened.
		 */
		bump_cpu_timer(timer, now);
	}

	if (unlikely(clear_dead)) {
		/*
		 * We've noticed that the thread is dead, but
		 * not yet reaped.  Take this opportunity to
		 * drop our task ref.
		 */
		clear_dead_task(timer, now);
		goto dead;
	}

	if (cpu_time_before(timer->it_clock, now, timer->it.cpu.expires)) {
		sample_to_timespec(timer->it_clock,
				   cpu_time_sub(timer->it_clock,
						timer->it.cpu.expires, now),
				   &itp->it_value);
	} else {
		/*
		 * The timer should have expired already, but the firing
		 * hasn't taken place yet.  Say it's just about to expire.
		 */
		itp->it_value.tv_nsec = 1;
		itp->it_value.tv_sec = 0;
	}
}