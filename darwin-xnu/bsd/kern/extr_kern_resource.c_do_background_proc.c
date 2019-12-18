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
 int EPERM ; 
#define  PRIO_DARWIN_BG 129 
#define  PRIO_DARWIN_NONUI 128 
 int /*<<< orphan*/  TASK_POLICY_DARWIN_BG ; 
 int TASK_POLICY_DISABLE ; 
 int TASK_POLICY_ENABLE ; 
 int TASK_POLICY_EXTERNAL ; 
 int TASK_POLICY_INTERNAL ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 scalar_t__ kauth_cred_getruid (int /*<<< orphan*/ ) ; 
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_issuser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_proc_ref (struct proc*) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int mac_proc_check_sched (struct proc*,struct proc*) ; 
 int /*<<< orphan*/  proc_set_task_policy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_task (struct proc*) ; 

__attribute__((used)) static int
do_background_proc(struct proc *curp, struct proc *targetp, int priority)
{
#if !CONFIG_MACF
#pragma unused(curp)
#endif
	int error = 0;
	kauth_cred_t ucred;
	kauth_cred_t target_cred;
	int external;
	int enable;

	ucred = kauth_cred_get();
	target_cred = kauth_cred_proc_ref(targetp);

	if (!kauth_cred_issuser(ucred) && kauth_cred_getruid(ucred) &&
		kauth_cred_getuid(ucred) != kauth_cred_getuid(target_cred) &&
		kauth_cred_getruid(ucred) != kauth_cred_getuid(target_cred))
	{
		error = EPERM;
		goto out;
	}

#if CONFIG_MACF
	error = mac_proc_check_sched(curp, targetp);
	if (error) 
		goto out;
#endif

	external = (curp == targetp) ? TASK_POLICY_INTERNAL : TASK_POLICY_EXTERNAL;

	switch (priority) {
		case PRIO_DARWIN_BG:
			enable = TASK_POLICY_ENABLE;
			break;
		case PRIO_DARWIN_NONUI:
			/* ignored for compatibility */
			goto out;
		default:
			/* TODO: EINVAL if priority != 0 */
			enable = TASK_POLICY_DISABLE;
			break;
	}

	proc_set_task_policy(proc_task(targetp), external, TASK_POLICY_DARWIN_BG, enable);

out:
	kauth_cred_unref(&target_cred);
	return (error);
}