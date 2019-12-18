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
struct vfsmount {TYPE_3__* mnt_root; TYPE_1__* mnt_sb; } ;
struct path {TYPE_4__* dentry; } ;
struct TYPE_10__ {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_mode; } ;
struct TYPE_9__ {TYPE_5__* d_inode; } ;
struct TYPE_8__ {TYPE_2__* d_inode; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_mode; } ;
struct TYPE_6__ {int s_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOTDIR ; 
 scalar_t__ IS_DEADDIR (TYPE_5__*) ; 
 int MS_NOUSER ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int attach_recursive_mnt (struct vfsmount*,struct path*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_unlinked (TYPE_4__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int security_sb_check_sb (struct vfsmount*,struct path*) ; 
 int /*<<< orphan*/  security_sb_post_addmount (struct vfsmount*,struct path*) ; 

__attribute__((used)) static int graft_tree(struct vfsmount *mnt, struct path *path)
{
	int err;
	if (mnt->mnt_sb->s_flags & MS_NOUSER)
		return -EINVAL;

	if (S_ISDIR(path->dentry->d_inode->i_mode) !=
	      S_ISDIR(mnt->mnt_root->d_inode->i_mode))
		return -ENOTDIR;

	err = -ENOENT;
	mutex_lock(&path->dentry->d_inode->i_mutex);
	if (IS_DEADDIR(path->dentry->d_inode))
		goto out_unlock;

	err = security_sb_check_sb(mnt, path);
	if (err)
		goto out_unlock;

	err = -ENOENT;
	if (!d_unlinked(path->dentry))
		err = attach_recursive_mnt(mnt, path, NULL);
out_unlock:
	mutex_unlock(&path->dentry->d_inode->i_mutex);
	if (!err)
		security_sb_post_addmount(mnt, path);
	return err;
}