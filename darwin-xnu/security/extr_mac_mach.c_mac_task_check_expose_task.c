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
struct ucred {int dummy; } ;
struct task {int dummy; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,struct ucred*,struct proc*) ; 
 struct ucred* kauth_cred_get () ; 
 struct proc* mac_task_get_proc (struct task*) ; 
 int /*<<< orphan*/  proc_check_expose_task ; 
 int /*<<< orphan*/  proc_rele (struct proc*) ; 

int
mac_task_check_expose_task(struct task *task)
{
	int error;

	struct proc *p = mac_task_get_proc(task);
	if (p == NULL)
		return ESRCH;

	struct ucred *cred = kauth_cred_get();
	MAC_CHECK(proc_check_expose_task, cred, p);
	proc_rele(p);
	return (error);
}