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
struct vfsmount {struct vfsmount* mnt_parent; struct dentry* mnt_mountpoint; } ;
struct path {int /*<<< orphan*/  dentry; struct vfsmount* mnt; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_subdir (struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_path_reachable(struct vfsmount *mnt, struct dentry *dentry,
			 const struct path *root)
{
	while (mnt != root->mnt && mnt->mnt_parent != mnt) {
		dentry = mnt->mnt_mountpoint;
		mnt = mnt->mnt_parent;
	}
	return mnt == root->mnt && is_subdir(dentry, root->dentry);
}