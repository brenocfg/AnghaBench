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
struct vfsmount {int /*<<< orphan*/  mnt_expire; } ;
struct path {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int do_add_mount_unlocked (struct vfsmount*,struct path*,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 int /*<<< orphan*/  namespace_sem ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int do_add_mount(struct vfsmount *newmnt, struct path *path,
		 int mnt_flags, struct list_head *fslist)
{
	int err;

	down_write(&namespace_sem);
	err = do_add_mount_unlocked(newmnt, path, mnt_flags);
	if (!err) {
		if (fslist) /* add to the specified expiration list */
			list_add_tail(&newmnt->mnt_expire, fslist);
	}
	up_write(&namespace_sem);
	if (err)
		mntput(newmnt);
	return err;
}