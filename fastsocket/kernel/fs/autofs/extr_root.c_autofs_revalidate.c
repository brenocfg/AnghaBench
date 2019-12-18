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
struct nameidata {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int d_flags; scalar_t__ d_time; TYPE_2__* d_inode; TYPE_1__* d_parent; } ;
struct autofs_sb_info {int /*<<< orphan*/  dirhash; } ;
struct autofs_dir_ent {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mode; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 scalar_t__ AUTOFS_NEGATIVE_TIMEOUT ; 
 int DCACHE_AUTOFS_PENDING ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ autofs_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  autofs_update_usage (int /*<<< orphan*/ *,struct autofs_dir_ent*) ; 
 int /*<<< orphan*/  d_mountpoint (struct dentry*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int try_to_fill_dentry (struct dentry*,int /*<<< orphan*/ ,struct autofs_sb_info*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int autofs_revalidate(struct dentry * dentry, struct nameidata *nd)
{
	struct inode * dir;
	struct autofs_sb_info *sbi;
	struct autofs_dir_ent *ent;
	int res;

	lock_kernel();
	dir = dentry->d_parent->d_inode;
	sbi = autofs_sbi(dir->i_sb);

	/* Pending dentry */
	if (dentry->d_flags & DCACHE_AUTOFS_PENDING) {
		if (autofs_oz_mode(sbi))
			res = 1;
		else
			res = try_to_fill_dentry(dentry, dir->i_sb, sbi);
		unlock_kernel();
		return res;
	}

	/* Negative dentry.. invalidate if "old" */
	if (!dentry->d_inode) {
		unlock_kernel();
		return (dentry->d_time - jiffies <= AUTOFS_NEGATIVE_TIMEOUT);
	}
		
	/* Check for a non-mountpoint directory */
	if (S_ISDIR(dentry->d_inode->i_mode) && !d_mountpoint(dentry)) {
		if (autofs_oz_mode(sbi))
			res = 1;
		else
			res = try_to_fill_dentry(dentry, dir->i_sb, sbi);
		unlock_kernel();
		return res;
	}

	/* Update the usage list */
	if (!autofs_oz_mode(sbi)) {
		ent = (struct autofs_dir_ent *) dentry->d_time;
		if (ent)
			autofs_update_usage(&sbi->dirhash,ent);
	}
	unlock_kernel();
	return 1;
}