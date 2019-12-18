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
struct super_block {struct cgroupfs_root* s_fs_info; } ;
struct cgroup {TYPE_2__* dentry; } ;
struct cgroupfs_root {scalar_t__ flags; int /*<<< orphan*/  release_agent_path; int /*<<< orphan*/  name; struct cgroup top_cgroup; } ;
struct cgroup_sb_opts {scalar_t__ flags; scalar_t__ name; scalar_t__ release_agent; int /*<<< orphan*/  subsys_bits; } ;
struct TYPE_4__ {TYPE_1__* d_inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 int /*<<< orphan*/  cgroup_populate_dir (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_root_mutex ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int parse_cgroupfs_options (char*,struct cgroup_sb_opts*) ; 
 int rebind_subsystems (struct cgroupfs_root*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int cgroup_remount(struct super_block *sb, int *flags, char *data)
{
	int ret = 0;
	struct cgroupfs_root *root = sb->s_fs_info;
	struct cgroup *cgrp = &root->top_cgroup;
	struct cgroup_sb_opts opts;

	lock_kernel();
	mutex_lock(&cgrp->dentry->d_inode->i_mutex);
	mutex_lock(&cgroup_mutex);
	mutex_lock(&cgroup_root_mutex);

	/* See what subsystems are wanted */
	ret = parse_cgroupfs_options(data, &opts);
	if (ret)
		goto out_unlock;

	/* Don't allow flags to change at remount */
	if (opts.flags != root->flags) {
		ret = -EINVAL;
		goto out_unlock;
	}

	/* Don't allow name to change at remount */
	if (opts.name && strcmp(opts.name, root->name)) {
		ret = -EINVAL;
		goto out_unlock;
	}

	ret = rebind_subsystems(root, opts.subsys_bits);
	if (ret)
		goto out_unlock;

	/* (re)populate subsystem files */
	cgroup_populate_dir(cgrp);

	if (opts.release_agent)
		strcpy(root->release_agent_path, opts.release_agent);
 out_unlock:
	kfree(opts.release_agent);
	kfree(opts.name);
	mutex_unlock(&cgroup_root_mutex);
	mutex_unlock(&cgroup_mutex);
	mutex_unlock(&cgrp->dentry->d_inode->i_mutex);
	unlock_kernel();
	return ret;
}