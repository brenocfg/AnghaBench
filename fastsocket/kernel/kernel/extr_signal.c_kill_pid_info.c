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
struct task_struct {int dummy; } ;
struct siginfo {int dummy; } ;
struct pid {int dummy; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int group_send_sig_info (int,struct siginfo*,struct task_struct*) ; 
 struct task_struct* pid_task (struct pid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

int kill_pid_info(int sig, struct siginfo *info, struct pid *pid)
{
	int error = -ESRCH;
	struct task_struct *p;

	rcu_read_lock();
retry:
	p = pid_task(pid, PIDTYPE_PID);
	if (p) {
		error = group_send_sig_info(sig, info, p);
		if (unlikely(error == -ESRCH))
			/*
			 * The task was unhashed in between, try again.
			 * If it is dead, pid_task() will return NULL,
			 * if we race with de_thread() it will find the
			 * new leader.
			 */
			goto retry;
	}
	rcu_read_unlock();

	return error;
}