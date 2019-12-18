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
struct cpuset {int relax_domain_level; struct cgroup_subsys_state css; struct cpuset* parent; int /*<<< orphan*/  fmeter; int /*<<< orphan*/  mems_allowed; int /*<<< orphan*/  cpus_allowed; scalar_t__ flags; } ;
struct cgroup_subsys {int dummy; } ;
struct cgroup {int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {struct cgroup_subsys_state css; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SCHED_LOAD_BALANCE ; 
 int /*<<< orphan*/  CS_SPREAD_PAGE ; 
 int /*<<< orphan*/  CS_SPREAD_SLAB ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct cgroup_subsys_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cpuset* cgroup_cs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmeter_init (int /*<<< orphan*/ *) ; 
 scalar_t__ is_spread_page (struct cpuset*) ; 
 scalar_t__ is_spread_slab (struct cpuset*) ; 
 int /*<<< orphan*/  kfree (struct cpuset*) ; 
 struct cpuset* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodes_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  number_of_cpusets ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_1__ top_cpuset ; 

__attribute__((used)) static struct cgroup_subsys_state *cpuset_create(
	struct cgroup_subsys *ss,
	struct cgroup *cont)
{
	struct cpuset *cs;
	struct cpuset *parent;

	if (!cont->parent) {
		return &top_cpuset.css;
	}
	parent = cgroup_cs(cont->parent);
	cs = kmalloc(sizeof(*cs), GFP_KERNEL);
	if (!cs)
		return ERR_PTR(-ENOMEM);
	if (!alloc_cpumask_var(&cs->cpus_allowed, GFP_KERNEL)) {
		kfree(cs);
		return ERR_PTR(-ENOMEM);
	}

	cs->flags = 0;
	if (is_spread_page(parent))
		set_bit(CS_SPREAD_PAGE, &cs->flags);
	if (is_spread_slab(parent))
		set_bit(CS_SPREAD_SLAB, &cs->flags);
	set_bit(CS_SCHED_LOAD_BALANCE, &cs->flags);
	cpumask_clear(cs->cpus_allowed);
	nodes_clear(cs->mems_allowed);
	fmeter_init(&cs->fmeter);
	cs->relax_domain_level = -1;

	cs->parent = parent;
	number_of_cpusets++;
	return &cs->css ;
}