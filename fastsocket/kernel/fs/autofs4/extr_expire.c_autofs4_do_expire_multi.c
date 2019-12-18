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
struct super_block {int dummy; } ;
struct dentry {int dummy; } ;
struct autofs_sb_info {int /*<<< orphan*/  fs_lock; int /*<<< orphan*/  type; } ;
struct autofs_info {int /*<<< orphan*/  expire_complete; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_INF_EXPIRING ; 
 int EAGAIN ; 
 int /*<<< orphan*/  NFY_EXPIRE ; 
 struct autofs_info* autofs4_dentry_ino (struct dentry*) ; 
 struct dentry* autofs4_expire_direct (struct super_block*,struct vfsmount*,struct autofs_sb_info*,int) ; 
 struct dentry* autofs4_expire_indirect (struct super_block*,struct vfsmount*,struct autofs_sb_info*,int) ; 
 int autofs4_wait (struct autofs_sb_info*,struct dentry*,int /*<<< orphan*/ ) ; 
 scalar_t__ autofs_type_trigger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int autofs4_do_expire_multi(struct super_block *sb, struct vfsmount *mnt,
			    struct autofs_sb_info *sbi, int when)
{
	struct dentry *dentry;
	int ret = -EAGAIN;

	if (autofs_type_trigger(sbi->type))
		dentry = autofs4_expire_direct(sb, mnt, sbi, when);
	else
		dentry = autofs4_expire_indirect(sb, mnt, sbi, when);

	if (dentry) {
		struct autofs_info *ino = autofs4_dentry_ino(dentry);

		/* This is synchronous because it makes the daemon a
                   little easier */
		ret = autofs4_wait(sbi, dentry, NFY_EXPIRE);

		spin_lock(&sbi->fs_lock);
		ino->flags &= ~AUTOFS_INF_EXPIRING;
		complete_all(&ino->expire_complete);
		spin_unlock(&sbi->fs_lock);
		dput(dentry);
	}

	return ret;
}