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
struct taskstats {int /*<<< orphan*/  nivcsw; int /*<<< orphan*/  nvcsw; int /*<<< orphan*/  version; } ;
struct task_struct {int /*<<< orphan*/  nivcsw; int /*<<< orphan*/  nvcsw; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  TASKSTATS_VERSION ; 
 int /*<<< orphan*/  bacct_add_tsk (struct taskstats*,struct task_struct*) ; 
 int /*<<< orphan*/  delayacct_add_tsk (struct taskstats*,struct task_struct*) ; 
 struct task_struct* find_task_by_vpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  memset (struct taskstats*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  xacct_add_tsk (struct taskstats*,struct task_struct*) ; 

__attribute__((used)) static int fill_pid(pid_t pid, struct task_struct *tsk,
		struct taskstats *stats)
{
	int rc = 0;

	if (!tsk) {
		rcu_read_lock();
		tsk = find_task_by_vpid(pid);
		if (tsk)
			get_task_struct(tsk);
		rcu_read_unlock();
		if (!tsk)
			return -ESRCH;
	} else
		get_task_struct(tsk);

	memset(stats, 0, sizeof(*stats));
	/*
	 * Each accounting subsystem adds calls to its functions to
	 * fill in relevant parts of struct taskstsats as follows
	 *
	 *	per-task-foo(stats, tsk);
	 */

	delayacct_add_tsk(stats, tsk);

	/* fill in basic acct fields */
	stats->version = TASKSTATS_VERSION;
	stats->nvcsw = tsk->nvcsw;
	stats->nivcsw = tsk->nivcsw;
	bacct_add_tsk(stats, tsk);

	/* fill in extended acct fields */
	xacct_add_tsk(stats, tsk);

	/* Define err: label here if needed */
	put_task_struct(tsk);
	return rc;

}