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
struct ns_cgroup {int dummy; } ;
struct cgroup_subsys {int dummy; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 struct ns_cgroup* cgroup_to_ns (struct cgroup*) ; 
 int /*<<< orphan*/  kfree (struct ns_cgroup*) ; 

__attribute__((used)) static void ns_destroy(struct cgroup_subsys *ss,
			struct cgroup *cgroup)
{
	struct ns_cgroup *ns_cgroup;

	ns_cgroup = cgroup_to_ns(cgroup);
	kfree(ns_cgroup);
}