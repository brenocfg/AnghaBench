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
typedef  int /*<<< orphan*/  u32 ;
struct task_struct {int dummy; } ;
struct task_security_struct {int /*<<< orphan*/  sid; } ;
struct TYPE_2__ {struct task_security_struct* security; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  SECCLASS_SECURITY ; 
 int /*<<< orphan*/  SECINITSID_SECURITY ; 
 TYPE_1__* __task_cred (struct task_struct*) ; 
 int avc_has_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int task_has_security(struct task_struct *tsk,
			     u32 perms)
{
	const struct task_security_struct *tsec;
	u32 sid = 0;

	rcu_read_lock();
	tsec = __task_cred(tsk)->security;
	if (tsec)
		sid = tsec->sid;
	rcu_read_unlock();
	if (!tsec)
		return -EACCES;

	return avc_has_perm(sid, SECINITSID_SECURITY,
			    SECCLASS_SECURITY, perms, NULL);
}