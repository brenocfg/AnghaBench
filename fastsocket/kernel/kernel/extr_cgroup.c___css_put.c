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
struct cgroup_subsys_state {int /*<<< orphan*/  refcnt; struct cgroup* cgroup; } ;
struct cgroup {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGRP_RELEASABLE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int atomic_sub_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgroup_wakeup_rmdir_waiter (struct cgroup*) ; 
 int /*<<< orphan*/  check_for_release (struct cgroup*) ; 
 scalar_t__ notify_on_release (struct cgroup*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __css_put(struct cgroup_subsys_state *css, int count)
{
	struct cgroup *cgrp = css->cgroup;
	int val;
	rcu_read_lock();
	val = atomic_sub_return(count, &css->refcnt);
	if (val == 1) {
		if (notify_on_release(cgrp)) {
			set_bit(CGRP_RELEASABLE, &cgrp->flags);
			check_for_release(cgrp);
		}
		cgroup_wakeup_rmdir_waiter(cgrp);
	}
	rcu_read_unlock();
	WARN_ON_ONCE(val < 1);
}