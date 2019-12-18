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
struct mm_struct {int dummy; } ;
struct cpuset {int /*<<< orphan*/  mems_allowed; } ;
struct cgroup_scanner {int /*<<< orphan*/  cg; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 struct cpuset* cgroup_cs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuset_change_task_nodemask (struct task_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpuset_migrate_mm (struct mm_struct*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  guarantee_online_mems (struct cpuset*,int /*<<< orphan*/ *) ; 
 int is_memory_migrate (struct cpuset*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  mpol_rebind_mm (struct mm_struct*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpuset_change_nodemask(struct task_struct *p,
				   struct cgroup_scanner *scan)
{
	struct mm_struct *mm;
	struct cpuset *cs;
	int migrate;
	const nodemask_t *oldmem = scan->data;
	nodemask_t newmems;

	cs = cgroup_cs(scan->cg);
	guarantee_online_mems(cs, &newmems);

	cpuset_change_task_nodemask(p, &newmems);

	mm = get_task_mm(p);
	if (!mm)
		return;

	migrate = is_memory_migrate(cs);

	mpol_rebind_mm(mm, &cs->mems_allowed);
	if (migrate)
		cpuset_migrate_mm(mm, oldmem, &cs->mems_allowed);
	mmput(mm);
}