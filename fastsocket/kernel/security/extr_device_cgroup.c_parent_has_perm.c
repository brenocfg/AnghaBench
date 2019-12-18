#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dev_exception_item {int dummy; } ;
struct TYPE_4__ {TYPE_1__* cgroup; } ;
struct dev_cgroup {TYPE_2__ css; } ;
struct cgroup {int dummy; } ;
struct TYPE_3__ {struct cgroup* parent; } ;

/* Variables and functions */
 struct dev_cgroup* cgroup_to_devcgroup (struct cgroup*) ; 
 int may_access (struct dev_cgroup*,struct dev_exception_item*) ; 

__attribute__((used)) static int parent_has_perm(struct dev_cgroup *childcg,
				  struct dev_exception_item *ex)
{
	struct cgroup *pcg = childcg->css.cgroup->parent;
	struct dev_cgroup *parent;

	if (!pcg)
		return 1;
	parent = cgroup_to_devcgroup(pcg);
	return may_access(parent, ex);
}