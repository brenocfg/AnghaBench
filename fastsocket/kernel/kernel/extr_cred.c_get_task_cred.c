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
struct cred {int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct cred* __task_cred (struct task_struct*) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

const struct cred *get_task_cred(struct task_struct *task)
{
	const struct cred *cred;

	rcu_read_lock();

	do {
		cred = __task_cred((task));
		BUG_ON(!cred);
	} while (!atomic_inc_not_zero(&((struct cred *)cred)->usage));

	rcu_read_unlock();
	return cred;
}