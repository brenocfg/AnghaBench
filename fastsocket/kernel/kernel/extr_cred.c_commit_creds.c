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
struct task_struct {struct cred const* cred; struct cred const* real_cred; scalar_t__ pdeath_signal; scalar_t__ mm; } ;
typedef  struct cred {scalar_t__ euid; scalar_t__ egid; scalar_t__ fsuid; scalar_t__ fsgid; scalar_t__ uid; scalar_t__ suid; scalar_t__ gid; scalar_t__ sgid; TYPE_1__* user; int /*<<< orphan*/  cap_permitted; int /*<<< orphan*/  usage; } const cred ;
struct TYPE_2__ {int /*<<< orphan*/  processes; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PROC_EVENT_GID ; 
 int /*<<< orphan*/  PROC_EVENT_UID ; 
 int /*<<< orphan*/  alter_cred_subscribers (struct cred const*,int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cap_issubset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  get_cred (struct cred const*) ; 
 int /*<<< orphan*/  kdebug (char*,struct cred const*,int,int) ; 
 int /*<<< orphan*/  key_fsgid_changed (struct task_struct*) ; 
 int /*<<< orphan*/  key_fsuid_changed (struct task_struct*) ; 
 int /*<<< orphan*/  proc_id_connector (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cred (struct cred const*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct cred const*,struct cred const*) ; 
 int read_cred_subscribers (struct cred const*) ; 
 int /*<<< orphan*/  sched_switch_user (struct task_struct*) ; 
 int /*<<< orphan*/  security_commit_creds (struct cred const*,struct cred const*) ; 
 int /*<<< orphan*/  set_dumpable (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  suid_dumpable ; 
 int /*<<< orphan*/  validate_creds (struct cred const*) ; 

int commit_creds(struct cred *new)
{
	struct task_struct *task = current;
	const struct cred *old = task->real_cred;

	kdebug("commit_creds(%p{%d,%d})", new,
	       atomic_read(&new->usage),
	       read_cred_subscribers(new));

	BUG_ON(task->cred != old);
#ifdef CONFIG_DEBUG_CREDENTIALS
	BUG_ON(read_cred_subscribers(old) < 2);
	validate_creds(old);
	validate_creds(new);
#endif
	BUG_ON(atomic_read(&new->usage) < 1);

	security_commit_creds(new, old);

	get_cred(new); /* we will require a ref for the subj creds too */

	/* dumpability changes */
	if (old->euid != new->euid ||
	    old->egid != new->egid ||
	    old->fsuid != new->fsuid ||
	    old->fsgid != new->fsgid ||
	    !cap_issubset(new->cap_permitted, old->cap_permitted)) {
		if (task->mm)
			set_dumpable(task->mm, suid_dumpable);
		task->pdeath_signal = 0;
		smp_wmb();
	}

	/* alter the thread keyring */
	if (new->fsuid != old->fsuid)
		key_fsuid_changed(task);
	if (new->fsgid != old->fsgid)
		key_fsgid_changed(task);

	/* do it
	 * - What if a process setreuid()'s and this brings the
	 *   new uid over his NPROC rlimit?  We can check this now
	 *   cheaply with the new uid cache, so if it matters
	 *   we should be checking for it.  -DaveM
	 */
	alter_cred_subscribers(new, 2);
	if (new->user != old->user)
		atomic_inc(&new->user->processes);
	rcu_assign_pointer(task->real_cred, new);
	rcu_assign_pointer(task->cred, new);
	if (new->user != old->user)
		atomic_dec(&old->user->processes);
	alter_cred_subscribers(old, -2);

	sched_switch_user(task);

	/* send notifications */
	if (new->uid   != old->uid  ||
	    new->euid  != old->euid ||
	    new->suid  != old->suid ||
	    new->fsuid != old->fsuid)
		proc_id_connector(task, PROC_EVENT_UID);

	if (new->gid   != old->gid  ||
	    new->egid  != old->egid ||
	    new->sgid  != old->sgid ||
	    new->fsgid != old->fsgid)
		proc_id_connector(task, PROC_EVENT_GID);

	/* release the old obj and subj refs both */
	put_cred(old);
	put_cred(old);
	return 0;
}