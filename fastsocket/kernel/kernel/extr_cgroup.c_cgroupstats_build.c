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
struct task_struct {int state; } ;
struct dentry {struct cgroup* d_fsdata; TYPE_2__* d_inode; TYPE_1__* d_sb; } ;
struct cgroupstats {int /*<<< orphan*/  nr_io_wait; int /*<<< orphan*/  nr_stopped; int /*<<< orphan*/  nr_uninterruptible; int /*<<< orphan*/  nr_sleeping; int /*<<< orphan*/  nr_running; } ;
struct cgroup_iter {int dummy; } ;
struct cgroup {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/ * s_op; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
#define  TASK_INTERRUPTIBLE 131 
#define  TASK_RUNNING 130 
#define  TASK_STOPPED 129 
#define  TASK_UNINTERRUPTIBLE 128 
 int /*<<< orphan*/  cgroup_iter_end (struct cgroup*,struct cgroup_iter*) ; 
 struct task_struct* cgroup_iter_next (struct cgroup*,struct cgroup_iter*) ; 
 int /*<<< orphan*/  cgroup_iter_start (struct cgroup*,struct cgroup_iter*) ; 
 int /*<<< orphan*/  cgroup_ops ; 
 int /*<<< orphan*/  delayacct_is_task_waiting_on_io (struct task_struct*) ; 

int cgroupstats_build(struct cgroupstats *stats, struct dentry *dentry)
{
	int ret = -EINVAL;
	struct cgroup *cgrp;
	struct cgroup_iter it;
	struct task_struct *tsk;

	/*
	 * Validate dentry by checking the superblock operations,
	 * and make sure it's a directory.
	 */
	if (dentry->d_sb->s_op != &cgroup_ops ||
	    !S_ISDIR(dentry->d_inode->i_mode))
		 goto err;

	ret = 0;
	cgrp = dentry->d_fsdata;

	cgroup_iter_start(cgrp, &it);
	while ((tsk = cgroup_iter_next(cgrp, &it))) {
		switch (tsk->state) {
		case TASK_RUNNING:
			stats->nr_running++;
			break;
		case TASK_INTERRUPTIBLE:
			stats->nr_sleeping++;
			break;
		case TASK_UNINTERRUPTIBLE:
			stats->nr_uninterruptible++;
			break;
		case TASK_STOPPED:
			stats->nr_stopped++;
			break;
		default:
			if (delayacct_is_task_waiting_on_io(tsk))
				stats->nr_io_wait++;
			break;
		}
	}
	cgroup_iter_end(cgrp, &it);

err:
	return ret;
}