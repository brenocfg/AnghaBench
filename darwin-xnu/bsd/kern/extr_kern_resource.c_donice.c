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
struct proc {int p_nice; int /*<<< orphan*/  p_acflag; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int EACCES ; 
 int EPERM ; 
 int PRIO_MAX ; 
 int PRIO_MIN ; 
 scalar_t__ kauth_cred_getruid (int /*<<< orphan*/ ) ; 
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_proc_ref (struct proc*) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int mac_proc_check_sched (struct proc*,struct proc*) ; 
 int /*<<< orphan*/  proc_lock (struct proc*) ; 
 int /*<<< orphan*/  proc_unlock (struct proc*) ; 
 int /*<<< orphan*/  resetpriority (struct proc*) ; 
 scalar_t__ suser (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
donice(struct proc *curp, struct proc *chgp, int n)
{
	int error = 0;
	kauth_cred_t ucred;
	kauth_cred_t my_cred;

	ucred = kauth_cred_proc_ref(curp);
	my_cred = kauth_cred_proc_ref(chgp);

	if (suser(ucred, NULL) && kauth_cred_getruid(ucred) &&
	    kauth_cred_getuid(ucred) != kauth_cred_getuid(my_cred) &&
	    kauth_cred_getruid(ucred) != kauth_cred_getuid(my_cred)) {
		error = EPERM;
		goto out;
	}
	if (n > PRIO_MAX)
		n = PRIO_MAX;
	if (n < PRIO_MIN)
		n = PRIO_MIN;
	if (n < chgp->p_nice && suser(ucred, &curp->p_acflag)) {
		error = EACCES;
		goto out;
	}
#if CONFIG_MACF
	error = mac_proc_check_sched(curp, chgp);
	if (error) 
		goto out;
#endif
	proc_lock(chgp);
	chgp->p_nice = n;
	proc_unlock(chgp);
	(void)resetpriority(chgp);
out:
	kauth_cred_unref(&ucred);
	kauth_cred_unref(&my_cred);
	return (error);
}