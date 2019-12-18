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
struct vfsmount {scalar_t__ mnt_root; } ;
struct path {scalar_t__ dentry; struct vfsmount* mnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 int MS_REC ; 
 int MS_SHARED ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  change_mnt_propagation (struct vfsmount*,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int invent_group_ids (struct vfsmount*,int) ; 
 int /*<<< orphan*/  namespace_sem ; 
 struct vfsmount* next_mnt (struct vfsmount*,struct vfsmount*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfsmount_lock ; 

__attribute__((used)) static int do_change_type(struct path *path, int flag)
{
	struct vfsmount *m, *mnt = path->mnt;
	int recurse = flag & MS_REC;
	int type = flag & ~MS_REC;
	int err = 0;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	if (path->dentry != path->mnt->mnt_root)
		return -EINVAL;

	down_write(&namespace_sem);
	if (type == MS_SHARED) {
		err = invent_group_ids(mnt, recurse);
		if (err)
			goto out_unlock;
	}

	spin_lock(&vfsmount_lock);
	for (m = mnt; m; m = (recurse ? next_mnt(m, mnt) : NULL))
		change_mnt_propagation(m, type);
	spin_unlock(&vfsmount_lock);

 out_unlock:
	up_write(&namespace_sem);
	return err;
}