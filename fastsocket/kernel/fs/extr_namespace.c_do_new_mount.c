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
struct path {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct vfsmount*) ; 
 int PTR_ERR (struct vfsmount*) ; 
 int __do_add_mount (struct vfsmount*,struct path*,int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct vfsmount* do_kern_mount (char*,int,char*,void*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int do_new_mount(struct path *path, char *type, int flags,
			int mnt_flags, char *name, void *data)
{
	struct vfsmount *mnt;
	int err;

	if (!type)
		return -EINVAL;

	/* we need capabilities... */
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	lock_kernel();
	mnt = do_kern_mount(type, flags, name, data);
	unlock_kernel();
	if (IS_ERR(mnt))
		return PTR_ERR(mnt);

	err = __do_add_mount(mnt, path, mnt_flags);
	if (err)
		mntput(mnt);
	return err;
}