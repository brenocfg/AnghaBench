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
struct vfsmount {int dummy; } ;
struct path {struct vfsmount* mnt; struct dentry* dentry; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; scalar_t__ len; } ;
struct dentry {int /*<<< orphan*/  d_sb; TYPE_1__ d_name; } ;
struct autofs_sb_info {int /*<<< orphan*/  type; } ;
struct autofs_info {int /*<<< orphan*/  last_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 struct autofs_info* autofs4_dentry_ino (struct dentry*) ; 
 struct autofs_sb_info* autofs4_sbi (int /*<<< orphan*/ ) ; 
 scalar_t__ autofs_type_indirect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  follow_down (struct path*) ; 
 scalar_t__ is_autofs4_dentry (struct dentry*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  may_umount_tree (struct vfsmount*) ; 
 int /*<<< orphan*/  path_get (struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 

__attribute__((used)) static int autofs4_mount_busy(struct vfsmount *mnt, struct dentry *dentry)
{
	struct dentry *top = dentry;
	struct path path = {.mnt = mnt, .dentry = dentry};
	int status = 1;

	DPRINTK("dentry %p %.*s",
		dentry, (int)dentry->d_name.len, dentry->d_name.name);

	path_get(&path);

	if (!follow_down(&path))
		goto done;

	if (is_autofs4_dentry(path.dentry)) {
		struct autofs_sb_info *sbi = autofs4_sbi(path.dentry->d_sb);

		/* This is an autofs submount, we can't expire it */
		if (autofs_type_indirect(sbi->type))
			goto done;
	}

	/* Update the expiry counter if fs is busy */
	if (!may_umount_tree(path.mnt)) {
		struct autofs_info *ino = autofs4_dentry_ino(top);
		ino->last_used = jiffies;
		goto done;
	}

	status = 0;
done:
	DPRINTK("returning = %d", status);
	path_put(&path);
	return status;
}