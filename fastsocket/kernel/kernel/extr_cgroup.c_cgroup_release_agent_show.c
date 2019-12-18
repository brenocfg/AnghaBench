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
struct cgroup {TYPE_1__* root; } ;
struct cftype {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  release_agent_path; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  cgroup_lock_live_group (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_unlock () ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cgroup_release_agent_show(struct cgroup *cgrp, struct cftype *cft,
				     struct seq_file *seq)
{
	if (!cgroup_lock_live_group(cgrp))
		return -ENODEV;
	seq_puts(seq, cgrp->root->release_agent_path);
	seq_putc(seq, '\n');
	cgroup_unlock();
	return 0;
}