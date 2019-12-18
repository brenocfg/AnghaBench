#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nameidata {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_sb; } ;
struct TYPE_7__ {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct dentry {int d_flags; scalar_t__ d_inode; int /*<<< orphan*/ * d_op; TYPE_1__ d_name; } ;
struct autofs_sb_info {int /*<<< orphan*/  catatonic; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_8__ {int /*<<< orphan*/  signal; } ;
struct TYPE_9__ {TYPE_2__ pending; } ;

/* Variables and functions */
 int DCACHE_AUTOFS_PENDING ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ERESTARTNOINTR ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ NAME_MAX ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  autofs_dentry_operations ; 
 int autofs_oz_mode (struct autofs_sb_info*) ; 
 int /*<<< orphan*/  autofs_revalidate (struct dentry*,struct nameidata*) ; 
 int /*<<< orphan*/  autofs_say (int /*<<< orphan*/ ,scalar_t__) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  d_add (struct dentry*,int /*<<< orphan*/ *) ; 
 scalar_t__ d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sigismember (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (TYPE_3__*) ; 
 int /*<<< orphan*/  task_pgrp_nr (TYPE_3__*) ; 
 int /*<<< orphan*/  task_pid_nr (TYPE_3__*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static struct dentry *autofs_root_lookup(struct inode *dir, struct dentry *dentry, struct nameidata *nd)
{
	struct autofs_sb_info *sbi;
	int oz_mode;

	DPRINTK(("autofs_root_lookup: name = "));
	lock_kernel();
	autofs_say(dentry->d_name.name,dentry->d_name.len);

	if (dentry->d_name.len > NAME_MAX) {
		unlock_kernel();
		return ERR_PTR(-ENAMETOOLONG);/* File name too long to exist */
	}

	sbi = autofs_sbi(dir->i_sb);

	oz_mode = autofs_oz_mode(sbi);
	DPRINTK(("autofs_lookup: pid = %u, pgrp = %u, catatonic = %d, "
				"oz_mode = %d\n", task_pid_nr(current),
				task_pgrp_nr(current), sbi->catatonic,
				oz_mode));

	/*
	 * Mark the dentry incomplete, but add it. This is needed so
	 * that the VFS layer knows about the dentry, and we can count
	 * on catching any lookups through the revalidate.
	 *
	 * Let all the hard work be done by the revalidate function that
	 * needs to be able to do this anyway..
	 *
	 * We need to do this before we release the directory semaphore.
	 */
	dentry->d_op = &autofs_dentry_operations;
	dentry->d_flags |= DCACHE_AUTOFS_PENDING;
	d_add(dentry, NULL);

	mutex_unlock(&dir->i_mutex);
	autofs_revalidate(dentry, nd);
	mutex_lock(&dir->i_mutex);

	/*
	 * If we are still pending, check if we had to handle
	 * a signal. If so we can force a restart..
	 */
	if (dentry->d_flags & DCACHE_AUTOFS_PENDING) {
		/* See if we were interrupted */
		if (signal_pending(current)) {
			sigset_t *sigset = &current->pending.signal;
			if (sigismember (sigset, SIGKILL) ||
			    sigismember (sigset, SIGQUIT) ||
			    sigismember (sigset, SIGINT)) {
				unlock_kernel();
				return ERR_PTR(-ERESTARTNOINTR);
			}
		}
	}
	unlock_kernel();

	/*
	 * If this dentry is unhashed, then we shouldn't honour this
	 * lookup even if the dentry is positive.  Returning ENOENT here
	 * doesn't do the right thing for all system calls, but it should
	 * be OK for the operations we permit from an autofs.
	 */
	if (dentry->d_inode && d_unhashed(dentry))
		return ERR_PTR(-ENOENT);

	return NULL;
}