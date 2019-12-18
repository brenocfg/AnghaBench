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
struct task_struct {int dummy; } ;
struct cgroup_scanner {int /*<<< orphan*/  cg; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpus_allowed; } ;

/* Variables and functions */
 TYPE_1__* cgroup_cs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpus_allowed_ptr (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpuset_change_cpumask(struct task_struct *tsk,
				  struct cgroup_scanner *scan)
{
	set_cpus_allowed_ptr(tsk, ((cgroup_cs(scan->cg))->cpus_allowed));
}