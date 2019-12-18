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
 int /*<<< orphan*/  SECCLASS_PROCESS ; 
 TYPE_1__* __task_cred (struct task_struct const*) ; 
 int avc_has_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int task_has_perm(const struct task_struct *tsk1,
			 const struct task_struct *tsk2,
			 u32 perms)
{
	const struct task_security_struct *__tsec1, *__tsec2;
	u32 sid1, sid2;

	rcu_read_lock();
	__tsec1 = __task_cred(tsk1)->security;	sid1 = __tsec1->sid;
	__tsec2 = __task_cred(tsk2)->security;	sid2 = __tsec2->sid;
	rcu_read_unlock();
	return avc_has_perm(sid1, sid2, SECCLASS_PROCESS, perms, NULL);
}