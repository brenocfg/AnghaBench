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
struct vfsmount {scalar_t__ mnt_sb; scalar_t__ mnt_root; int /*<<< orphan*/  mnt_expire; int /*<<< orphan*/  mnt_count; } ;
struct path {scalar_t__ dentry; TYPE_1__* mnt; } ;
struct TYPE_2__ {scalar_t__ mnt_sb; int mnt_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ELOOP ; 
 int MNT_SHRINKABLE ; 
 int __do_add_mount (struct vfsmount*,struct path*,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 int /*<<< orphan*/  namespace_sem ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfsmount_lock ; 

int finish_automount(struct vfsmount *m, struct path *path)
{
	int err;
	/* The new mount record should have at least 2 refs to prevent it being
	 * expired before we get a chance to add it
	 */
	BUG_ON(atomic_read(&m->mnt_count) < 2);

	if (m->mnt_sb == path->mnt->mnt_sb &&
	    m->mnt_root == path->dentry) {
		err = -ELOOP;
		goto fail;
	}

	err = __do_add_mount(m, path, path->mnt->mnt_flags | MNT_SHRINKABLE);
	if (!err)
		return 0;
fail:
	/* remove m from any expiration list it may be on */
	if (!list_empty(&m->mnt_expire)) {
		down_write(&namespace_sem);
		spin_lock(&vfsmount_lock);
		list_del_init(&m->mnt_expire);
		spin_unlock(&vfsmount_lock);
		up_write(&namespace_sem);
	}
	mntput(m);
	mntput(m);
	return err;
}