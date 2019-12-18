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
struct task_struct {int /*<<< orphan*/  comm; } ;
struct seq_file {int dummy; } ;
struct pid {int dummy; } ;
struct cpu_workqueue_stats {int /*<<< orphan*/  executed; int /*<<< orphan*/  inserted; int /*<<< orphan*/  cpu; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct pid* find_get_pid (int /*<<< orphan*/ ) ; 
 struct task_struct* get_pid_task (struct pid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pid (struct pid*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int workqueue_stat_show(struct seq_file *s, void *p)
{
	struct cpu_workqueue_stats *cws = p;
	struct pid *pid;
	struct task_struct *tsk;

	pid = find_get_pid(cws->pid);
	if (pid) {
		tsk = get_pid_task(pid, PIDTYPE_PID);
		if (tsk) {
			seq_printf(s, "%3d %6d     %6u       %s\n", cws->cpu,
				   atomic_read(&cws->inserted), cws->executed,
				   tsk->comm);
			put_task_struct(tsk);
		}
		put_pid(pid);
	}

	return 0;
}