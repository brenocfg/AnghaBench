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
struct seq_file {struct cgroup_pidlist* private; } ;
struct file {int f_mode; scalar_t__ private_data; int /*<<< orphan*/ * f_op; TYPE_1__* f_dentry; } ;
struct cgroup_pidlist {int dummy; } ;
struct cgroup {int dummy; } ;
typedef  enum cgroup_filetype { ____Placeholder_cgroup_filetype } cgroup_filetype ;
struct TYPE_2__ {int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 int FMODE_READ ; 
 struct cgroup* __d_cgrp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_pidlist_operations ; 
 int /*<<< orphan*/  cgroup_pidlist_seq_operations ; 
 int /*<<< orphan*/  cgroup_release_pid_array (struct cgroup_pidlist*) ; 
 int pidlist_array_load (struct cgroup*,int,struct cgroup_pidlist**) ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cgroup_pidlist_open(struct file *file, enum cgroup_filetype type)
{
	struct cgroup *cgrp = __d_cgrp(file->f_dentry->d_parent);
	struct cgroup_pidlist *l;
	int retval;

	/* Nothing to do for write-only files */
	if (!(file->f_mode & FMODE_READ))
		return 0;

	/* have the array populated */
	retval = pidlist_array_load(cgrp, type, &l);
	if (retval)
		return retval;
	/* configure file information */
	file->f_op = &cgroup_pidlist_operations;

	retval = seq_open(file, &cgroup_pidlist_seq_operations);
	if (retval) {
		cgroup_release_pid_array(l);
		return retval;
	}
	((struct seq_file *)file->private_data)->private = l;
	return 0;
}