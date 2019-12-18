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
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_lock; struct cgroup* d_fsdata; } ;
struct cgroup {int /*<<< orphan*/  flags; TYPE_1__* dentry; int /*<<< orphan*/  root; int /*<<< orphan*/  sibling; int /*<<< orphan*/  release_list; int /*<<< orphan*/  children; int /*<<< orphan*/  count; struct cgroup* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGRP_RELEASABLE ; 
 int /*<<< orphan*/  CGRP_REMOVED ; 
 int /*<<< orphan*/  CGRP_WAIT_ON_RMDIR ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EINTR ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int cgroup_call_pre_destroy (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_clear_css_refs (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_d_remove_dir (struct dentry*) ; 
 int /*<<< orphan*/  cgroup_lock_hierarchy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 int /*<<< orphan*/  cgroup_rmdir_waitq ; 
 int /*<<< orphan*/  cgroup_unlock_hierarchy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_for_release (struct cgroup*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 struct dentry* dget (TYPE_1__*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_list_lock ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int cgroup_rmdir(struct inode *unused_dir, struct dentry *dentry)
{
	struct cgroup *cgrp = dentry->d_fsdata;
	struct dentry *d;
	struct cgroup *parent;
	DEFINE_WAIT(wait);
	int ret;

	/* the vfs holds both inode->i_mutex already */
again:
	mutex_lock(&cgroup_mutex);
	if (atomic_read(&cgrp->count) != 0) {
		mutex_unlock(&cgroup_mutex);
		return -EBUSY;
	}
	if (!list_empty(&cgrp->children)) {
		mutex_unlock(&cgroup_mutex);
		return -EBUSY;
	}
	mutex_unlock(&cgroup_mutex);

	/*
	 * In general, subsystem has no css->refcnt after pre_destroy(). But
	 * in racy cases, subsystem may have to get css->refcnt after
	 * pre_destroy() and it makes rmdir return with -EBUSY. This sometimes
	 * make rmdir return -EBUSY too often. To avoid that, we use waitqueue
	 * for cgroup's rmdir. CGRP_WAIT_ON_RMDIR is for synchronizing rmdir
	 * and subsystem's reference count handling. Please see css_get/put
	 * and css_tryget() and cgroup_wakeup_rmdir_waiter() implementation.
	 */
	set_bit(CGRP_WAIT_ON_RMDIR, &cgrp->flags);

	/*
	 * Call pre_destroy handlers of subsys. Notify subsystems
	 * that rmdir() request comes.
	 */
	ret = cgroup_call_pre_destroy(cgrp);
	if (ret) {
		clear_bit(CGRP_WAIT_ON_RMDIR, &cgrp->flags);
		return ret;
	}

	mutex_lock(&cgroup_mutex);
	parent = cgrp->parent;
	if (atomic_read(&cgrp->count) || !list_empty(&cgrp->children)) {
		clear_bit(CGRP_WAIT_ON_RMDIR, &cgrp->flags);
		mutex_unlock(&cgroup_mutex);
		return -EBUSY;
	}
	prepare_to_wait(&cgroup_rmdir_waitq, &wait, TASK_INTERRUPTIBLE);
	if (!cgroup_clear_css_refs(cgrp)) {
		mutex_unlock(&cgroup_mutex);
		/*
		 * Because someone may call cgroup_wakeup_rmdir_waiter() before
		 * prepare_to_wait(), we need to check this flag.
		 */
		if (test_bit(CGRP_WAIT_ON_RMDIR, &cgrp->flags))
			schedule();
		finish_wait(&cgroup_rmdir_waitq, &wait);
		clear_bit(CGRP_WAIT_ON_RMDIR, &cgrp->flags);
		if (signal_pending(current))
			return -EINTR;
		goto again;
	}
	/* NO css_tryget() can success after here. */
	finish_wait(&cgroup_rmdir_waitq, &wait);
	clear_bit(CGRP_WAIT_ON_RMDIR, &cgrp->flags);

	spin_lock(&release_list_lock);
	set_bit(CGRP_REMOVED, &cgrp->flags);
	if (!list_empty(&cgrp->release_list))
		list_del(&cgrp->release_list);
	spin_unlock(&release_list_lock);

	cgroup_lock_hierarchy(cgrp->root);
	/* delete this cgroup from parent->children */
	list_del(&cgrp->sibling);
	cgroup_unlock_hierarchy(cgrp->root);

	spin_lock(&cgrp->dentry->d_lock);
	d = dget(cgrp->dentry);
	spin_unlock(&d->d_lock);

	cgroup_d_remove_dir(d);
	dput(d);

	set_bit(CGRP_RELEASABLE, &parent->flags);
	check_for_release(parent);

	mutex_unlock(&cgroup_mutex);
	return 0;
}