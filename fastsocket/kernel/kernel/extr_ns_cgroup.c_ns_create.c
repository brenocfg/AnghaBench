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
struct cgroup_subsys_state {int dummy; } ;
struct ns_cgroup {struct cgroup_subsys_state css; } ;
struct cgroup_subsys {int dummy; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EPERM ; 
 struct cgroup_subsys_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_is_descendant (struct cgroup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 struct ns_cgroup* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cgroup_subsys_state *ns_create(struct cgroup_subsys *ss,
						struct cgroup *cgroup)
{
	struct ns_cgroup *ns_cgroup;

	if (!capable(CAP_SYS_ADMIN))
		return ERR_PTR(-EPERM);
	if (!cgroup_is_descendant(cgroup, current))
		return ERR_PTR(-EPERM);

	ns_cgroup = kzalloc(sizeof(*ns_cgroup), GFP_KERNEL);
	if (!ns_cgroup)
		return ERR_PTR(-ENOMEM);
	return &ns_cgroup->css;
}