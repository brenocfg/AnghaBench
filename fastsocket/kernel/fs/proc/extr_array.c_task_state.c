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
struct task_struct {scalar_t__ files; int /*<<< orphan*/  real_parent; } ;
struct seq_file {int dummy; } ;
struct pid_namespace {int dummy; } ;
struct pid {int dummy; } ;
struct group_info {int /*<<< orphan*/  ngroups; } ;
struct fdtable {int /*<<< orphan*/  max_fds; } ;
struct cred {struct group_info* group_info; int /*<<< orphan*/  fsgid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  egid; int /*<<< orphan*/  gid; int /*<<< orphan*/  fsuid; int /*<<< orphan*/  suid; int /*<<< orphan*/  euid; int /*<<< orphan*/  uid; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  GROUP_AT (struct group_info*,int) ; 
 int /*<<< orphan*/  NGROUPS_SMALL ; 
 struct fdtable* files_fdtable (scalar_t__) ; 
 struct cred* get_task_cred (struct task_struct*) ; 
 int /*<<< orphan*/  get_task_state (struct task_struct*) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pid_alive (struct task_struct*) ; 
 int /*<<< orphan*/  pid_nr_ns (struct pid*,struct pid_namespace*) ; 
 int /*<<< orphan*/  put_cred (struct cred const*) ; 
 struct task_struct* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 scalar_t__ task_pid_nr_ns (struct task_struct*,struct pid_namespace*) ; 
 scalar_t__ task_tgid_nr_ns (struct task_struct*,struct pid_namespace*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 int /*<<< orphan*/  task_utrace_proc_status (struct seq_file*,struct task_struct*) ; 
 struct task_struct* tracehook_tracer_task (struct task_struct*) ; 

__attribute__((used)) static inline void task_state(struct seq_file *m, struct pid_namespace *ns,
				struct pid *pid, struct task_struct *p)
{
	struct group_info *group_info;
	int g;
	struct fdtable *fdt = NULL;
	const struct cred *cred;
	pid_t ppid, tpid;

	rcu_read_lock();
	ppid = pid_alive(p) ?
		task_tgid_nr_ns(rcu_dereference(p->real_parent), ns) : 0;
	tpid = 0;
	if (pid_alive(p)) {
		struct task_struct *tracer = tracehook_tracer_task(p);
		if (tracer)
			tpid = task_pid_nr_ns(tracer, ns);
	}
	cred = get_task_cred(p);
	seq_printf(m,
		"State:\t%s\n"
		"Tgid:\t%d\n"
		"Pid:\t%d\n"
		"PPid:\t%d\n"
		"TracerPid:\t%d\n"
		"Uid:\t%d\t%d\t%d\t%d\n"
		"Gid:\t%d\t%d\t%d\t%d\n",
		get_task_state(p),
		task_tgid_nr_ns(p, ns),
		pid_nr_ns(pid, ns),
		ppid, tpid,
		cred->uid, cred->euid, cred->suid, cred->fsuid,
		cred->gid, cred->egid, cred->sgid, cred->fsgid);

	task_utrace_proc_status(m, p);

	task_lock(p);
	if (p->files)
		fdt = files_fdtable(p->files);
	seq_printf(m,
		"FDSize:\t%d\n"
		"Groups:\t",
		fdt ? fdt->max_fds : 0);
	rcu_read_unlock();

	group_info = cred->group_info;
	task_unlock(p);

	for (g = 0; g < min(group_info->ngroups, NGROUPS_SMALL); g++)
		seq_printf(m, "%d ", GROUP_AT(group_info, g));
	put_cred(cred);

	seq_printf(m, "\n");
}