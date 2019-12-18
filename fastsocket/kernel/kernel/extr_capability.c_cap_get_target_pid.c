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
struct task_struct {int dummy; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  kernel_cap_t ;

/* Variables and functions */
 int ESRCH ; 
 struct task_struct* current ; 
 struct task_struct* find_task_by_vpid (scalar_t__) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int security_capget (struct task_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ task_pid_vnr (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 

__attribute__((used)) static inline int cap_get_target_pid(pid_t pid, kernel_cap_t *pEp,
				     kernel_cap_t *pIp, kernel_cap_t *pPp)
{
	int ret;

	if (pid && (pid != task_pid_vnr(current))) {
		struct task_struct *target;

		read_lock(&tasklist_lock);

		target = find_task_by_vpid(pid);
		if (!target)
			ret = -ESRCH;
		else
			ret = security_capget(target, pEp, pIp, pPp);

		read_unlock(&tasklist_lock);
	} else
		ret = security_capget(current, pEp, pIp, pPp);

	return ret;
}