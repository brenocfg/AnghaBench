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
struct seq_file {int dummy; } ;
struct cgroup_subsys {int /*<<< orphan*/  disabled; TYPE_1__* root; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  number_of_cgroups; int /*<<< orphan*/  hierarchy_id; } ;

/* Variables and functions */
 int CGROUP_SUBSYS_COUNT ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 struct cgroup_subsys** subsys ; 

__attribute__((used)) static int proc_cgroupstats_show(struct seq_file *m, void *v)
{
	int i;

	seq_puts(m, "#subsys_name\thierarchy\tnum_cgroups\tenabled\n");
	mutex_lock(&cgroup_mutex);
	for (i = 0; i < CGROUP_SUBSYS_COUNT; i++) {
		struct cgroup_subsys *ss = subsys[i];
		seq_printf(m, "%s\t%d\t%d\t%d\n",
			   ss->name, ss->root->hierarchy_id,
			   ss->root->number_of_cgroups, !ss->disabled);
	}
	mutex_unlock(&cgroup_mutex);
	return 0;
}