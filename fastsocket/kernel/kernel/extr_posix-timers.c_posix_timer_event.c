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
struct task_struct {int dummy; } ;
struct k_itimer {int it_sigev_notify; TYPE_2__* sigq; int /*<<< orphan*/  it_pid; } ;
struct TYPE_3__ {int si_sys_private; } ;
struct TYPE_4__ {TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int SIGEV_THREAD_ID ; 
 struct task_struct* pid_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int send_sigqueue (TYPE_2__*,struct task_struct*,int) ; 

int posix_timer_event(struct k_itimer *timr, int si_private)
{
	struct task_struct *task;
	int shared, ret = -1;
	/*
	 * FIXME: if ->sigq is queued we can race with
	 * dequeue_signal()->do_schedule_next_timer().
	 *
	 * If dequeue_signal() sees the "right" value of
	 * si_sys_private it calls do_schedule_next_timer().
	 * We re-queue ->sigq and drop ->it_lock().
	 * do_schedule_next_timer() locks the timer
	 * and re-schedules it while ->sigq is pending.
	 * Not really bad, but not that we want.
	 */
	timr->sigq->info.si_sys_private = si_private;

	rcu_read_lock();
	task = pid_task(timr->it_pid, PIDTYPE_PID);
	if (task) {
		shared = !(timr->it_sigev_notify & SIGEV_THREAD_ID);
		ret = send_sigqueue(timr->sigq, task, shared);
	}
	rcu_read_unlock();
	/* If we failed to send the signal the timer stops. */
	return ret > 0;
}