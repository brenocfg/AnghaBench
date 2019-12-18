#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct file_lock {int fl_flags; TYPE_4__* fl_ops; int /*<<< orphan*/ * fl_lmops; struct file* fl_file; int /*<<< orphan*/  fl_pid; int /*<<< orphan*/  fl_owner; int /*<<< orphan*/  fl_end; scalar_t__ fl_start; int /*<<< orphan*/  fl_type; } ;
struct TYPE_8__ {TYPE_2__* dentry; } ;
struct file {TYPE_3__ f_path; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;
struct TYPE_10__ {int /*<<< orphan*/  tgid; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* fl_release_private ) (struct file_lock*) ;} ;
struct TYPE_7__ {TYPE_1__* d_inode; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_flock; } ;

/* Variables and functions */
 int FL_CLOSE ; 
 int FL_POSIX ; 
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  OFFSET_MAX ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  stub1 (struct file_lock*) ; 
 int /*<<< orphan*/  vfs_lock_file (struct file*,int /*<<< orphan*/ ,struct file_lock*,int /*<<< orphan*/ *) ; 

void locks_remove_posix(struct file *filp, fl_owner_t owner)
{
	struct file_lock lock;

	/*
	 * If there are no locks held on this file, we don't need to call
	 * posix_lock_file().  Another process could be setting a lock on this
	 * file at the same time, but we wouldn't remove that lock anyway.
	 */
	if (!filp->f_path.dentry->d_inode->i_flock)
		return;

	lock.fl_type = F_UNLCK;
	lock.fl_flags = FL_POSIX | FL_CLOSE;
	lock.fl_start = 0;
	lock.fl_end = OFFSET_MAX;
	lock.fl_owner = owner;
	lock.fl_pid = current->tgid;
	lock.fl_file = filp;
	lock.fl_ops = NULL;
	lock.fl_lmops = NULL;

	vfs_lock_file(filp, F_SETLK, &lock, NULL);

	if (lock.fl_ops && lock.fl_ops->fl_release_private)
		lock.fl_ops->fl_release_private(&lock);
}