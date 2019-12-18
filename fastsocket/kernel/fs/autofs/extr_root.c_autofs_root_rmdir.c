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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dentry {unsigned long d_time; TYPE_1__ d_name; } ;
struct autofs_dirhash {int dummy; } ;
struct autofs_sb_info {struct autofs_dirhash dirhash; } ;
struct autofs_dir_ent {struct dentry* dentry; scalar_t__ ino; } ;

/* Variables and functions */
 unsigned int AUTOFS_FIRST_DIR_INO ; 
 int EACCES ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  autofs_hash_delete (struct autofs_dir_ent*) ; 
 struct autofs_dir_ent* autofs_hash_lookup (struct autofs_dirhash*,TYPE_1__*) ; 
 int /*<<< orphan*/  autofs_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int autofs_root_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct autofs_sb_info *sbi = autofs_sbi(dir->i_sb);
	struct autofs_dirhash *dh = &sbi->dirhash;
	struct autofs_dir_ent *ent;

	lock_kernel();
	if (!autofs_oz_mode(sbi)) {
		unlock_kernel();
		return -EACCES;
	}

	ent = autofs_hash_lookup(dh, &dentry->d_name);
	if (!ent) {
		unlock_kernel();
		return -ENOENT;
	}

	if ((unsigned int)ent->ino < AUTOFS_FIRST_DIR_INO) {
		unlock_kernel();
		return -ENOTDIR; /* Not a directory */
	}

	if (ent->dentry != dentry) {
		printk("autofs_rmdir: odentry != dentry for entry %s\n", dentry->d_name.name);
	}

	dentry->d_time = (unsigned long)(struct autofs_dir_ent *)NULL;
	autofs_hash_delete(ent);
	drop_nlink(dir);
	d_drop(dentry);
	unlock_kernel();

	return 0;
}