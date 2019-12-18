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
struct vfsmount {int dummy; } ;
struct path {int /*<<< orphan*/  dentry; int /*<<< orphan*/  mnt; } ;

/* Variables and functions */
 struct vfsmount* __lookup_mnt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mntget (struct vfsmount*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfsmount_lock ; 

struct vfsmount *lookup_mnt(struct path *path)
{
	struct vfsmount *child_mnt;
	spin_lock(&vfsmount_lock);
	if ((child_mnt = __lookup_mnt(path->mnt, path->dentry, 1)))
		mntget(child_mnt);
	spin_unlock(&vfsmount_lock);
	return child_mnt;
}