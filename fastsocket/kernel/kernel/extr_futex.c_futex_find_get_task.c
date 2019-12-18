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
struct cred {scalar_t__ euid; scalar_t__ uid; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 struct task_struct* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESRCH ; 
 struct cred* __task_cred (struct task_struct*) ; 
 struct cred* current_cred () ; 
 struct task_struct* find_task_by_vpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct task_struct * futex_find_get_task(pid_t pid)
{
	struct task_struct *p;
	const struct cred *cred = current_cred(), *pcred;

	rcu_read_lock();
	p = find_task_by_vpid(pid);
	if (!p) {
		p = ERR_PTR(-ESRCH);
	} else {
		pcred = __task_cred(p);
		if (cred->euid != pcred->euid &&
		    cred->euid != pcred->uid)
			p = ERR_PTR(-ESRCH);
		else
			get_task_struct(p);
	}

	rcu_read_unlock();

	return p;
}