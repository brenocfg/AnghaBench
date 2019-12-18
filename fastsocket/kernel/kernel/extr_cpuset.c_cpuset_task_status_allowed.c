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
struct task_struct {int /*<<< orphan*/  mems_allowed; int /*<<< orphan*/  cpus_allowed; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_cpumask (struct seq_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_cpumask_list (struct seq_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_nodemask (struct seq_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_nodemask_list (struct seq_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*) ; 

void cpuset_task_status_allowed(struct seq_file *m, struct task_struct *task)
{
	seq_printf(m, "Cpus_allowed:\t");
	seq_cpumask(m, &task->cpus_allowed);
	seq_printf(m, "\n");
	seq_printf(m, "Cpus_allowed_list:\t");
	seq_cpumask_list(m, &task->cpus_allowed);
	seq_printf(m, "\n");
	seq_printf(m, "Mems_allowed:\t");
	seq_nodemask(m, &task->mems_allowed);
	seq_printf(m, "\n");
	seq_printf(m, "Mems_allowed_list:\t");
	seq_nodemask_list(m, &task->mems_allowed);
	seq_printf(m, "\n");
}