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
struct cgroup_subsys_state {int /*<<< orphan*/  cgroup; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_wakeup_rmdir_waiter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  css_put (struct cgroup_subsys_state*) ; 

void cgroup_release_and_wakeup_rmdir(struct cgroup_subsys_state *css)
{
	cgroup_wakeup_rmdir_waiter(css->cgroup);
	css_put(css);
}