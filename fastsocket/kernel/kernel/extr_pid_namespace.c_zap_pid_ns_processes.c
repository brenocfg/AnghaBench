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
struct pid_namespace {scalar_t__ reboot; } ;
struct TYPE_4__ {TYPE_1__* signal; } ;
struct TYPE_3__ {scalar_t__ group_exit_code; } ;

/* Variables and functions */
 int ECHILD ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  TIF_SIGPENDING ; 
 int /*<<< orphan*/  __WALL ; 
 int /*<<< orphan*/  acct_exit_ns (struct pid_namespace*) ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  find_vpid (int) ; 
 int /*<<< orphan*/  force_sig (int /*<<< orphan*/ ,struct task_struct*) ; 
 int next_pidmap (struct pid_namespace*,int) ; 
 struct task_struct* pid_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int sys_wait4 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklist_lock ; 

void zap_pid_ns_processes(struct pid_namespace *pid_ns)
{
	int nr;
	int rc;
	struct task_struct *task;

	/*
	 * The last thread in the cgroup-init thread group is terminating.
	 * Find remaining pid_ts in the namespace, signal and wait for them
	 * to exit.
	 *
	 * Note:  This signals each threads in the namespace - even those that
	 * 	  belong to the same thread group, To avoid this, we would have
	 * 	  to walk the entire tasklist looking a processes in this
	 * 	  namespace, but that could be unnecessarily expensive if the
	 * 	  pid namespace has just a few processes. Or we need to
	 * 	  maintain a tasklist for each pid namespace.
	 *
	 */
	read_lock(&tasklist_lock);
	nr = next_pidmap(pid_ns, 1);
	while (nr > 0) {
		rcu_read_lock();

		/*
		 * Use force_sig() since it clears SIGNAL_UNKILLABLE ensuring
		 * any nested-container's init processes don't ignore the
		 * signal
		 */
		task = pid_task(find_vpid(nr), PIDTYPE_PID);
		if (task)
			force_sig(SIGKILL, task);

		rcu_read_unlock();

		nr = next_pidmap(pid_ns, nr);
	}
	read_unlock(&tasklist_lock);

	do {
		clear_thread_flag(TIF_SIGPENDING);
		rc = sys_wait4(-1, NULL, __WALL, NULL);
	} while (rc != -ECHILD);

	if (pid_ns->reboot)
		current->signal->group_exit_code = pid_ns->reboot;

	acct_exit_ns(pid_ns);
	return;
}