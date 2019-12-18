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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {unsigned long d_time; int /*<<< orphan*/  d_name; } ;
struct autofs_dirhash {int dummy; } ;
struct autofs_sb_info {TYPE_1__* symlink; int /*<<< orphan*/  symlink_bitmap; struct autofs_dirhash dirhash; } ;
struct autofs_dir_ent {unsigned int ino; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 unsigned int AUTOFS_FIRST_SYMLINK ; 
 unsigned int AUTOFS_MAX_SYMLINKS ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int EINVAL ; 
 int EISDIR ; 
 int ENOENT ; 
 int /*<<< orphan*/  autofs_hash_delete (struct autofs_dir_ent*) ; 
 struct autofs_dir_ent* autofs_hash_lookup (struct autofs_dirhash*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  autofs_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  test_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int autofs_root_unlink(struct inode *dir, struct dentry *dentry)
{
	struct autofs_sb_info *sbi = autofs_sbi(dir->i_sb);
	struct autofs_dirhash *dh = &sbi->dirhash;
	struct autofs_dir_ent *ent;
	unsigned int n;

	/* This allows root to remove symlinks */
	lock_kernel();
	if (!autofs_oz_mode(sbi) && !capable(CAP_SYS_ADMIN)) {
		unlock_kernel();
		return -EACCES;
	}

	ent = autofs_hash_lookup(dh, &dentry->d_name);
	if (!ent) {
		unlock_kernel();
		return -ENOENT;
	}

	n = ent->ino - AUTOFS_FIRST_SYMLINK;
	if (n >= AUTOFS_MAX_SYMLINKS) {
		unlock_kernel();
		return -EISDIR;	/* It's a directory, dummy */
	}
	if (!test_bit(n,sbi->symlink_bitmap)) {
		unlock_kernel();
		return -EINVAL;	/* Nonexistent symlink?  Shouldn't happen */
	}
	
	dentry->d_time = (unsigned long)(struct autofs_dirhash *)NULL;
	autofs_hash_delete(ent);
	clear_bit(n,sbi->symlink_bitmap);
	kfree(sbi->symlink[n].data);
	d_drop(dentry);
	
	unlock_kernel();
	return 0;
}