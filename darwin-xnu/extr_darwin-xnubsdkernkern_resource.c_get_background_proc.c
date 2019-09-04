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
 int /*<<< orphan*/  TASK_POLICY_DARWIN_BG ; 
 int TASK_POLICY_EXTERNAL ; 
 int TASK_POLICY_INTERNAL ; 
 int /*<<< orphan*/  current_task () ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 scalar_t__ kauth_cred_getruid (int /*<<< orphan*/ ) ; 
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_issuser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_proc_ref (struct proc*) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int proc_get_task_policy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_background_proc(struct proc *curp, struct proc *targetp, int *priority)
{
	int external = 0;
	int error = 0;
	kauth_cred_t ucred, target_cred;

	ucred = kauth_cred_get();
	target_cred = kauth_cred_proc_ref(targetp);

	if (!kauth_cred_issuser(ucred) && kauth_cred_getruid(ucred) &&
	    kauth_cred_getuid(ucred) != kauth_cred_getuid(target_cred) &&
	    kauth_cred_getruid(ucred) != kauth_cred_getuid(target_cred)) {
		error = EPERM;
		goto out;
	}

	external = (curp == targetp) ? TASK_POLICY_INTERNAL : TASK_POLICY_EXTERNAL;

	*priority = proc_get_task_policy(current_task(), external, TASK_POLICY_DARWIN_BG);

out:
	kauth_cred_unref(&target_cred);
	return (error);
}