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
struct cgroup_scanner {int /*<<< orphan*/  cg; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_cs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuset_update_task_spread_flag (int /*<<< orphan*/ ,struct task_struct*) ; 

__attribute__((used)) static void cpuset_change_flag(struct task_struct *tsk,
				struct cgroup_scanner *scan)
{
	cpuset_update_task_spread_flag(cgroup_cs(scan->cg), tsk);
}