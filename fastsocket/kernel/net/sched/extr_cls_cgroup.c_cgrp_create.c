#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cgroup_subsys_state {int dummy; } ;
struct cgroup_subsys {int dummy; } ;
struct cgroup_cls_state {struct cgroup_subsys_state css; int /*<<< orphan*/  classid; } ;
struct cgroup {scalar_t__ parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  classid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct cgroup_subsys_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* cgrp_cls_state (scalar_t__) ; 
 struct cgroup_cls_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cgroup_subsys_state *cgrp_create(struct cgroup_subsys *ss,
						 struct cgroup *cgrp)
{
	struct cgroup_cls_state *cs;

	if (!(cs = kzalloc(sizeof(*cs), GFP_KERNEL)))
		return ERR_PTR(-ENOMEM);

	if (cgrp->parent)
		cs->classid = cgrp_cls_state(cgrp->parent)->classid;

	return &cs->css;
}