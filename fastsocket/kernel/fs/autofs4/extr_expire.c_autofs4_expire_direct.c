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
struct super_block {int /*<<< orphan*/  s_root; } ;
struct dentry {int dummy; } ;
struct autofs_sb_info {unsigned long exp_timeout; int /*<<< orphan*/  fs_lock; } ;
struct autofs_info {int flags; int /*<<< orphan*/  expire_complete; } ;

/* Variables and functions */
 int AUTOFS_EXP_IMMEDIATE ; 
 int AUTOFS_INF_EXPIRING ; 
 int AUTOFS_INF_PENDING ; 
 struct autofs_info* autofs4_dentry_ino (struct dentry*) ; 
 int /*<<< orphan*/  autofs4_direct_busy (struct vfsmount*,struct dentry*,unsigned long,int) ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct dentry *autofs4_expire_direct(struct super_block *sb,
				     struct vfsmount *mnt,
				     struct autofs_sb_info *sbi,
				     int how)
{
	unsigned long timeout;
	struct dentry *root = dget(sb->s_root);
	int do_now = how & AUTOFS_EXP_IMMEDIATE;
	struct autofs_info *ino;

	if (!root)
		return NULL;

	now = jiffies;
	timeout = sbi->exp_timeout;

	spin_lock(&sbi->fs_lock);
	ino = autofs4_dentry_ino(root);
	/* No point expiring a pending mount */
	if (ino->flags & AUTOFS_INF_PENDING)
		goto out;
	if (!autofs4_direct_busy(mnt, root, timeout, do_now)) {
		struct autofs_info *ino = autofs4_dentry_ino(root);
		ino->flags |= AUTOFS_INF_EXPIRING;
		init_completion(&ino->expire_complete);
		spin_unlock(&sbi->fs_lock);
		return root;
	}
out:
	spin_unlock(&sbi->fs_lock);
	dput(root);

	return NULL;
}