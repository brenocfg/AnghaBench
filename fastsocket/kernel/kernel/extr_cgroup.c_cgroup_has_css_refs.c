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
struct cgroup_subsys_state {int /*<<< orphan*/  refcnt; } ;
struct cgroup_subsys {scalar_t__ root; size_t subsys_id; } ;
struct cgroup {scalar_t__ root; struct cgroup_subsys_state** subsys; } ;

/* Variables and functions */
 int CGROUP_SUBSYS_COUNT ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct cgroup_subsys** subsys ; 

__attribute__((used)) static int cgroup_has_css_refs(struct cgroup *cgrp)
{
	/* Check the reference count on each subsystem. Since we
	 * already established that there are no tasks in the
	 * cgroup, if the css refcount is also 1, then there should
	 * be no outstanding references, so the subsystem is safe to
	 * destroy. We scan across all subsystems rather than using
	 * the per-hierarchy linked list of mounted subsystems since
	 * we can be called via check_for_release() with no
	 * synchronization other than RCU, and the subsystem linked
	 * list isn't RCU-safe */
	int i;
	for (i = 0; i < CGROUP_SUBSYS_COUNT; i++) {
		struct cgroup_subsys *ss = subsys[i];
		struct cgroup_subsys_state *css;
		/* Skip subsystems not in this hierarchy */
		if (ss->root != cgrp->root)
			continue;
		css = cgrp->subsys[ss->subsys_id];
		/* When called from check_for_release() it's possible
		 * that by this point the cgroup has been removed
		 * and the css deleted. But a false-positive doesn't
		 * matter, since it can only happen if the cgroup
		 * has been deleted and hence no longer needs the
		 * release agent to be called anyway. */
		if (css && (atomic_read(&css->refcnt) > 1))
			return 1;
	}
	return 0;
}