#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int mnt_flags; } ;
struct timespec {int dummy; } ;
struct inode {int i_flags; TYPE_1__* i_sb; struct timespec i_atime; int /*<<< orphan*/  i_mode; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_4__ {int s_flags; } ;

/* Variables and functions */
 scalar_t__ IS_NOATIME (struct inode*) ; 
 int MNT_NOATIME ; 
 int MNT_NODIRATIME ; 
 int MS_NODIRATIME ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int S_NOATIME ; 
 int /*<<< orphan*/  __mnt_drop_write (struct vfsmount*) ; 
 scalar_t__ __mnt_want_write (struct vfsmount*) ; 
 struct timespec current_fs_time (TYPE_1__*) ; 
 int /*<<< orphan*/  mark_inode_dirty_sync (struct inode*) ; 
 int /*<<< orphan*/  relatime_need_update (struct vfsmount*,struct inode*,struct timespec) ; 
 int /*<<< orphan*/  sb_end_write (TYPE_1__*) ; 
 int /*<<< orphan*/  sb_start_write_trylock (TYPE_1__*) ; 
 scalar_t__ timespec_equal (struct timespec*,struct timespec*) ; 

void touch_atime(struct vfsmount *mnt, struct dentry *dentry)
{
	struct inode *inode = dentry->d_inode;
	struct timespec now;

	if (inode->i_flags & S_NOATIME)
		return;
	if (IS_NOATIME(inode))
		return;
	if ((inode->i_sb->s_flags & MS_NODIRATIME) && S_ISDIR(inode->i_mode))
		return;

	if (mnt->mnt_flags & MNT_NOATIME)
		return;
	if ((mnt->mnt_flags & MNT_NODIRATIME) && S_ISDIR(inode->i_mode))
		return;

	now = current_fs_time(inode->i_sb);

	if (!relatime_need_update(mnt, inode, now))
		return;

	if (timespec_equal(&inode->i_atime, &now))
		return;

	if (!sb_start_write_trylock(inode->i_sb))
		return;

	if (__mnt_want_write(mnt))
		goto skip_update;

	inode->i_atime = now;
	mark_inode_dirty_sync(inode);
	__mnt_drop_write(mnt);
skip_update:
	sb_end_write(inode->i_sb);
}