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
typedef  scalar_t__ proc_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  TASK_POLICY_ATTRIBUTE ; 
 int /*<<< orphan*/  TASK_POLICY_ROLE ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 scalar_t__ kauth_cred_getruid (int /*<<< orphan*/ ) ; 
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_issuser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_proc_ref (scalar_t__) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int mac_proc_check_sched (scalar_t__,scalar_t__) ; 
 int proc_get_task_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_task (scalar_t__) ; 
 int proc_task_role_to_darwin_role (int) ; 

__attribute__((used)) static int
proc_get_darwin_role(proc_t curp, proc_t targetp, int *priority)
{
	int error = 0;
	int role = 0;

	kauth_cred_t ucred, target_cred;

	ucred = kauth_cred_get();
	target_cred = kauth_cred_proc_ref(targetp);

	if (!kauth_cred_issuser(ucred) && kauth_cred_getruid(ucred) &&
	    kauth_cred_getuid(ucred)  != kauth_cred_getuid(target_cred) &&
	    kauth_cred_getruid(ucred) != kauth_cred_getuid(target_cred)) {
		error = EPERM;
		goto out;
	}

	if (curp != targetp) {
#if CONFIG_MACF
		if ((error = mac_proc_check_sched(curp, targetp)))
			goto out;
#endif
	}

	role = proc_get_task_policy(proc_task(targetp), TASK_POLICY_ATTRIBUTE, TASK_POLICY_ROLE);

	*priority = proc_task_role_to_darwin_role(role);

out:
	kauth_cred_unref(&target_cred);
	return (error);
}