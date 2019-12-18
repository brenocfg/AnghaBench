#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int int32_t ;
struct TYPE_9__ {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int,...) ; 
 int EINVAL ; 
 int EPERM ; 
 int ESRCH ; 
 int /*<<< orphan*/  SIGKILL ; 
 int SIGTERM ; 
 int /*<<< orphan*/  TASK_POLICY_ATTRIBUTE ; 
 int /*<<< orphan*/  TASK_POLICY_ENABLE ; 
 int /*<<< orphan*/  TASK_POLICY_TERMINATED ; 
 int /*<<< orphan*/  cansignal (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* current_proc () ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int memorystatus_on_terminate (TYPE_1__*) ; 
 TYPE_1__* proc_find (int) ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_set_task_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process ; 
 int /*<<< orphan*/  psignal (TYPE_1__*,int) ; 
 int /*<<< orphan*/  signum ; 

int
proc_terminate(int pid, int32_t *retval)
{
	int error = 0;
	proc_t p;
	kauth_cred_t uc = kauth_cred_get();
	int sig;

#if 0
	/* XXX: Check if these are necessary */
	AUDIT_ARG(pid, pid);
	AUDIT_ARG(signum, sig);
#endif

	if (pid <= 0 || retval == NULL) {
		return (EINVAL);
	}

	if ((p = proc_find(pid)) == NULL) {
		return (ESRCH);
	}

#if 0
	/* XXX: Check if these are necessary */
	AUDIT_ARG(process, p);
#endif

	/* Check privileges; if SIGKILL can be issued, then SIGTERM is also OK */
	if (!cansignal(current_proc(), uc, p, SIGKILL)) {
		error = EPERM;
		goto out;
	}

	/* Not allowed to sudden terminate yourself */
	if (p == current_proc()) {
		error = EPERM;
		goto out;
	}

#if CONFIG_MEMORYSTATUS
	/* Determine requisite signal to issue */
	sig = memorystatus_on_terminate(p);
#else
	sig = SIGTERM;
#endif

	proc_set_task_policy(p->task, TASK_POLICY_ATTRIBUTE,
	                     TASK_POLICY_TERMINATED, TASK_POLICY_ENABLE);

	psignal(p, sig);
	*retval = sig;

out:
	proc_rele(p);
	
	return error;
}