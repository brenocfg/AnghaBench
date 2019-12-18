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
struct task_struct {TYPE_1__* pids; struct task_struct* group_leader; } ;
struct pid_namespace {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  enum pid_type { ____Placeholder_pid_type } pid_type ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int PIDTYPE_PID ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_alive (struct task_struct*) ; 
 int /*<<< orphan*/  pid_nr_ns (int /*<<< orphan*/ ,struct pid_namespace*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct pid_namespace* task_active_pid_ns (int /*<<< orphan*/ ) ; 

pid_t __task_pid_nr_ns(struct task_struct *task, enum pid_type type,
			struct pid_namespace *ns)
{
	pid_t nr = 0;

	rcu_read_lock();
	if (!ns)
		ns = task_active_pid_ns(current);
	if (likely(pid_alive(task))) {
		if (type != PIDTYPE_PID)
			task = task->group_leader;
		nr = pid_nr_ns(task->pids[type].pid, ns);
	}
	rcu_read_unlock();

	return nr;
}