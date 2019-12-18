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
struct TYPE_2__ {char const* name; int /*<<< orphan*/  len; int /*<<< orphan*/  hash; } ;
struct dentry {TYPE_1__ d_name; } ;
struct autofs_symlink {int len; int /*<<< orphan*/  mtime; struct autofs_dir_ent* data; } ;
struct autofs_dirhash {int dummy; } ;
struct autofs_sb_info {int /*<<< orphan*/  symlink_bitmap; struct autofs_symlink* symlink; struct autofs_dirhash dirhash; } ;
struct autofs_dir_ent {scalar_t__ ino; int /*<<< orphan*/ * dentry; int /*<<< orphan*/  len; struct autofs_dir_ent* name; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 scalar_t__ AUTOFS_FIRST_SYMLINK ; 
 unsigned int AUTOFS_MAX_SYMLINKS ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int EACCES ; 
 int EEXIST ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  autofs_hash_insert (struct autofs_dirhash*,struct autofs_dir_ent*) ; 
 scalar_t__ autofs_hash_lookup (struct autofs_dirhash*,TYPE_1__*) ; 
 struct inode* autofs_iget (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  autofs_oz_mode (struct autofs_sb_info*) ; 
 int /*<<< orphan*/  autofs_say (char const*,int /*<<< orphan*/ ) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 unsigned int find_first_zero_bit (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int /*<<< orphan*/  kfree (struct autofs_dir_ent*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  memcpy (struct autofs_dir_ent*,char const*,int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int autofs_root_symlink(struct inode *dir, struct dentry *dentry, const char *symname)
{
	struct autofs_sb_info *sbi = autofs_sbi(dir->i_sb);
	struct autofs_dirhash *dh = &sbi->dirhash;
	struct autofs_dir_ent *ent;
	unsigned int n;
	int slsize;
	struct autofs_symlink *sl;
	struct inode *inode;

	DPRINTK(("autofs_root_symlink: %s <- ", symname));
	autofs_say(dentry->d_name.name,dentry->d_name.len);

	lock_kernel();
	if (!autofs_oz_mode(sbi)) {
		unlock_kernel();
		return -EACCES;
	}

	if (autofs_hash_lookup(dh, &dentry->d_name)) {
		unlock_kernel();
		return -EEXIST;
	}

	n = find_first_zero_bit(sbi->symlink_bitmap,AUTOFS_MAX_SYMLINKS);
	if (n >= AUTOFS_MAX_SYMLINKS) {
		unlock_kernel();
		return -ENOSPC;
	}

	set_bit(n,sbi->symlink_bitmap);
	sl = &sbi->symlink[n];
	sl->len = strlen(symname);
	sl->data = kmalloc(slsize = sl->len+1, GFP_KERNEL);
	if (!sl->data) {
		clear_bit(n,sbi->symlink_bitmap);
		unlock_kernel();
		return -ENOSPC;
	}

	ent = kmalloc(sizeof(struct autofs_dir_ent), GFP_KERNEL);
	if (!ent) {
		kfree(sl->data);
		clear_bit(n,sbi->symlink_bitmap);
		unlock_kernel();
		return -ENOSPC;
	}

	ent->name = kmalloc(dentry->d_name.len+1, GFP_KERNEL);
	if (!ent->name) {
		kfree(sl->data);
		kfree(ent);
		clear_bit(n,sbi->symlink_bitmap);
		unlock_kernel();
		return -ENOSPC;
	}

	memcpy(sl->data,symname,slsize);
	sl->mtime = get_seconds();

	ent->ino = AUTOFS_FIRST_SYMLINK + n;
	ent->hash = dentry->d_name.hash;
	memcpy(ent->name, dentry->d_name.name, 1+(ent->len = dentry->d_name.len));
	ent->dentry = NULL;	/* We don't keep the dentry for symlinks */

	autofs_hash_insert(dh,ent);

	inode = autofs_iget(dir->i_sb, ent->ino);
	if (IS_ERR(inode))
		return PTR_ERR(inode);

	d_instantiate(dentry, inode);
	unlock_kernel();
	return 0;
}