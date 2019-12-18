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
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  hash; } ;
struct dentry {TYPE_1__ d_name; } ;
struct autofs_dirhash {int dummy; } ;
struct autofs_sb_info {scalar_t__ next_dir_ino; struct autofs_dirhash dirhash; } ;
struct autofs_dir_ent {struct dentry* dentry; scalar_t__ ino; int /*<<< orphan*/  len; void* name; int /*<<< orphan*/  hash; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 scalar_t__ AUTOFS_FIRST_DIR_INO ; 
 int EACCES ; 
 int EEXIST ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  autofs_hash_insert (struct autofs_dirhash*,struct autofs_dir_ent*) ; 
 struct autofs_dir_ent* autofs_hash_lookup (struct autofs_dirhash*,TYPE_1__*) ; 
 struct inode* autofs_iget (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  autofs_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct autofs_dir_ent*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int autofs_root_mkdir(struct inode *dir, struct dentry *dentry, int mode)
{
	struct autofs_sb_info *sbi = autofs_sbi(dir->i_sb);
	struct autofs_dirhash *dh = &sbi->dirhash;
	struct autofs_dir_ent *ent;
	struct inode *inode;
	ino_t ino;

	lock_kernel();
	if (!autofs_oz_mode(sbi)) {
		unlock_kernel();
		return -EACCES;
	}

	ent = autofs_hash_lookup(dh, &dentry->d_name);
	if (ent) {
		unlock_kernel();
		return -EEXIST;
	}

	if (sbi->next_dir_ino < AUTOFS_FIRST_DIR_INO) {
		printk("autofs: Out of inode numbers -- what the heck did you do??\n");
		unlock_kernel();
		return -ENOSPC;
	}
	ino = sbi->next_dir_ino++;

	ent = kmalloc(sizeof(struct autofs_dir_ent), GFP_KERNEL);
	if (!ent) {
		unlock_kernel();
		return -ENOSPC;
	}

	ent->name = kmalloc(dentry->d_name.len+1, GFP_KERNEL);
	if (!ent->name) {
		kfree(ent);
		unlock_kernel();
		return -ENOSPC;
	}

	ent->hash = dentry->d_name.hash;
	memcpy(ent->name, dentry->d_name.name, 1+(ent->len = dentry->d_name.len));
	ent->ino = ino;
	ent->dentry = dentry;
	autofs_hash_insert(dh,ent);

	inc_nlink(dir);

	inode = autofs_iget(dir->i_sb, ino);
	if (IS_ERR(inode)) {
		drop_nlink(dir);
		return PTR_ERR(inode);
	}

	d_instantiate(dentry, inode);
	unlock_kernel();

	return 0;
}