#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {TYPE_2__* d_inode; TYPE_1__ d_name; int /*<<< orphan*/  d_sb; } ;
struct autofs_sb_info {int /*<<< orphan*/  fs_lock; } ;
struct autofs_info {int flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int AUTOFS_INF_EXPIRING ; 
 int /*<<< orphan*/  DPRINTK (char*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EISDIR ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 struct autofs_info* autofs4_dentry_ino (struct dentry*) ; 
 int autofs4_mount_wait (struct dentry*) ; 
 scalar_t__ autofs4_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs4_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_mountpoint (struct dentry*) ; 
 int /*<<< orphan*/  do_expire_wait (struct dentry*) ; 
 int /*<<< orphan*/  simple_empty (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int autofs4_d_manage(struct dentry *dentry, bool mounting_here)
{
	struct autofs_sb_info *sbi = autofs4_sbi(dentry->d_sb);
	struct autofs_info *ino = autofs4_dentry_ino(dentry);
	int status;

	DPRINTK("dentry=%p %.*s",
		dentry, dentry->d_name.len, dentry->d_name.name);

	/* The daemon never waits. */
	if (autofs4_oz_mode(sbi) || mounting_here) {
		if (!d_mountpoint(dentry))
			return -EISDIR;
		return 0;
	}

	/* Wait for pending expires */
	do_expire_wait(dentry);

	/*
	 * This dentry may be under construction so wait on mount
	 * completion.
	 */
	status = autofs4_mount_wait(dentry);
	if (status)
		return status;

	spin_lock(&sbi->fs_lock);
	/*
	 * If the dentry has been selected for expire while we slept
	 * on the lock then it might go away. We'll deal with that in
	 * ->d_automount() and wait on a new mount if the expire
	 * succeeds or return here if it doesn't (since there's no
	 * mount to follow with a rootless multi-mount).
	 */
	if (!(ino->flags & AUTOFS_INF_EXPIRING)) {
		/*
		 * Any needed mounting has been completed and the path
		 * updated so check if this is a rootless multi-mount so
		 * we can avoid needless calls ->d_automount() and avoid
		 * an incorrect ELOOP error return.
		 */
		if ((!d_mountpoint(dentry) && !simple_empty(dentry)) ||
		    (dentry->d_inode && S_ISLNK(dentry->d_inode->i_mode)))
			status = -EISDIR;
	}
	spin_unlock(&sbi->fs_lock);

	return status;
}