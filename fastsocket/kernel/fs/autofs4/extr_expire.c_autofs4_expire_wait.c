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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {TYPE_1__ d_name; int /*<<< orphan*/  d_sb; } ;
struct autofs_sb_info {int /*<<< orphan*/  fs_lock; } ;
struct autofs_info {int flags; int /*<<< orphan*/  expire_complete; } ;

/* Variables and functions */
 int AUTOFS_INF_EXPIRING ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  NFY_NONE ; 
 struct autofs_info* autofs4_dentry_ino (struct dentry*) ; 
 struct autofs_sb_info* autofs4_sbi (int /*<<< orphan*/ ) ; 
 int autofs4_wait (struct autofs_sb_info*,struct dentry*,int /*<<< orphan*/ ) ; 
 scalar_t__ d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int autofs4_expire_wait(struct dentry *dentry)
{
	struct autofs_sb_info *sbi = autofs4_sbi(dentry->d_sb);
	struct autofs_info *ino = autofs4_dentry_ino(dentry);
	int status;

	/* Block on any pending expire */
	spin_lock(&sbi->fs_lock);
	if (ino->flags & AUTOFS_INF_EXPIRING) {
		spin_unlock(&sbi->fs_lock);

		DPRINTK("waiting for expire %p name=%.*s",
			 dentry, dentry->d_name.len, dentry->d_name.name);

		status = autofs4_wait(sbi, dentry, NFY_NONE);
		wait_for_completion(&ino->expire_complete);

		DPRINTK("expire done status=%d", status);

		if (d_unhashed(dentry))
			return -EAGAIN;

		return status;
	}
	spin_unlock(&sbi->fs_lock);

	return 0;
}