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
struct vfsmount {int /*<<< orphan*/  mnt_mountpoint; struct vfsmount* mnt_parent; } ;
struct path {struct vfsmount* mnt; struct dentry* dentry; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  mntget (struct vfsmount*) ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfsmount_lock ; 

int follow_up(struct path *path)
{
	struct vfsmount *parent;
	struct dentry *mountpoint;
	spin_lock(&vfsmount_lock);
	parent = path->mnt->mnt_parent;
	if (parent == path->mnt) {
		spin_unlock(&vfsmount_lock);
		return 0;
	}
	mntget(parent);
	mountpoint = dget(path->mnt->mnt_mountpoint);
	spin_unlock(&vfsmount_lock);
	dput(path->dentry);
	path->dentry = mountpoint;
	mntput(path->mnt);
	path->mnt = parent;
	return 1;
}