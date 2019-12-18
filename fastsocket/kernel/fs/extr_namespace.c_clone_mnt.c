#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vfsmount {int /*<<< orphan*/  mnt_expire; struct vfsmount* mnt_master; int /*<<< orphan*/  mnt_slave; int /*<<< orphan*/  mnt_share; int /*<<< orphan*/  mnt_slave_list; struct vfsmount* mnt_parent; int /*<<< orphan*/  mnt_root; int /*<<< orphan*/  mnt_mountpoint; struct super_block* mnt_sb; int /*<<< orphan*/  mnt_flags; scalar_t__ mnt_group_id; int /*<<< orphan*/  mnt_devname; } ;
struct super_block {int /*<<< orphan*/  s_active; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_MNT_SHARED (struct vfsmount*) ; 
 int CL_EXPIRE ; 
 int CL_MAKE_SHARED ; 
 int CL_PRIVATE ; 
 int CL_PROPAGATION ; 
 int CL_SLAVE ; 
 scalar_t__ IS_MNT_SHARED (struct vfsmount*) ; 
 scalar_t__ IS_MNT_SLAVE (struct vfsmount*) ; 
 struct vfsmount* alloc_vfsmnt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  free_vfsmnt (struct vfsmount*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int mnt_alloc_group_id (struct vfsmount*) ; 
 int /*<<< orphan*/  set_mnt_shared (struct vfsmount*) ; 

__attribute__((used)) static struct vfsmount *clone_mnt(struct vfsmount *old, struct dentry *root,
					int flag)
{
	struct super_block *sb = old->mnt_sb;
	struct vfsmount *mnt = alloc_vfsmnt(old->mnt_devname);

	if (mnt) {
		if (flag & (CL_SLAVE | CL_PRIVATE))
			mnt->mnt_group_id = 0; /* not a peer of original */
		else
			mnt->mnt_group_id = old->mnt_group_id;

		if ((flag & CL_MAKE_SHARED) && !mnt->mnt_group_id) {
			int err = mnt_alloc_group_id(mnt);
			if (err)
				goto out_free;
		}

		mnt->mnt_flags = old->mnt_flags;
		atomic_inc(&sb->s_active);
		mnt->mnt_sb = sb;
		mnt->mnt_root = dget(root);
		mnt->mnt_mountpoint = mnt->mnt_root;
		mnt->mnt_parent = mnt;

		if (flag & CL_SLAVE) {
			list_add(&mnt->mnt_slave, &old->mnt_slave_list);
			mnt->mnt_master = old;
			CLEAR_MNT_SHARED(mnt);
		} else if (!(flag & CL_PRIVATE)) {
			if ((flag & CL_PROPAGATION) || IS_MNT_SHARED(old))
				list_add(&mnt->mnt_share, &old->mnt_share);
			if (IS_MNT_SLAVE(old))
				list_add(&mnt->mnt_slave, &old->mnt_slave);
			mnt->mnt_master = old->mnt_master;
		}
		if (flag & CL_MAKE_SHARED)
			set_mnt_shared(mnt);

		/* stick the duplicate mount on the same expiry list
		 * as the original if that was on one */
		if (flag & CL_EXPIRE) {
			if (!list_empty(&old->mnt_expire))
				list_add(&mnt->mnt_expire, &old->mnt_expire);
		}
	}
	return mnt;

 out_free:
	free_vfsmnt(mnt);
	return NULL;
}