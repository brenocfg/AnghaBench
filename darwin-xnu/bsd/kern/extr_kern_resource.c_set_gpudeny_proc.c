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
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  FALSE ; 
#define  PRIO_DARWIN_GPU_ALLOW 129 
#define  PRIO_DARWIN_GPU_DENY 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 scalar_t__ kauth_cred_getruid (int /*<<< orphan*/ ) ; 
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_issuser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_proc_ref (struct proc*) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int mac_proc_check_sched (struct proc*,struct proc*) ; 
 int /*<<< orphan*/  proc_task (struct proc*) ; 
 int /*<<< orphan*/  task_set_gpu_denied (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_gpudeny_proc(struct proc *curp, struct proc *targetp, int priority)
{
	int error = 0;
	kauth_cred_t ucred;
	kauth_cred_t target_cred;

	ucred = kauth_cred_get();
	target_cred = kauth_cred_proc_ref(targetp);

	/* TODO: Entitlement instead of uid check */

	if (!kauth_cred_issuser(ucred) && kauth_cred_getruid(ucred) &&
	    kauth_cred_getuid(ucred)   != kauth_cred_getuid(target_cred) &&
	    kauth_cred_getruid(ucred)  != kauth_cred_getuid(target_cred)) {
		error = EPERM;
		goto out;
	}

	if (curp == targetp) {
		error = EPERM;
		goto out;
	}

#if CONFIG_MACF
	error = mac_proc_check_sched(curp, targetp);
	if (error)
		goto out;
#endif

	switch (priority) {
		case PRIO_DARWIN_GPU_DENY:
			task_set_gpu_denied(proc_task(targetp), TRUE);
			break;
		case PRIO_DARWIN_GPU_ALLOW:
			task_set_gpu_denied(proc_task(targetp), FALSE);
			break;
		default:
			error = EINVAL;
			goto out;
	}

out:
	kauth_cred_unref(&target_cred);
	return (error);

}