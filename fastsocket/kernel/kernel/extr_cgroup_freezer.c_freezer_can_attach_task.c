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
struct cgroup {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ __cgroup_freezing_or_frozen (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int freezer_can_attach_task(struct cgroup *cgrp, struct task_struct *tsk)
{
	rcu_read_lock();
	if (__cgroup_freezing_or_frozen(tsk)) {
		rcu_read_unlock();
		return -EBUSY;
	}
	rcu_read_unlock();
	return 0;
}