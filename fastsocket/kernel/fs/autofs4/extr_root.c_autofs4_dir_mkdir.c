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
struct inode {int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {struct dentry* d_parent; struct autofs_info* d_fsdata; TYPE_1__ d_name; } ;
struct autofs_sb_info {int version; } ;
struct autofs_info {int /*<<< orphan*/  count; int /*<<< orphan*/  dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int /*<<< orphan*/  DPRINTK (char*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int ENOMEM ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  autofs4_del_active (struct dentry*) ; 
 struct autofs_info* autofs4_dentry_ino (struct dentry*) ; 
 struct inode* autofs4_get_inode (int /*<<< orphan*/ ,struct autofs_info*) ; 
 struct autofs_info* autofs4_init_ino (struct autofs_info*,struct autofs_sb_info*,int) ; 
 int /*<<< orphan*/  autofs4_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs4_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  autofs_set_leaf_automount_flags (struct dentry*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct autofs_info*) ; 

__attribute__((used)) static int autofs4_dir_mkdir(struct inode *dir, struct dentry *dentry, int mode)
{
	struct autofs_sb_info *sbi = autofs4_sbi(dir->i_sb);
	struct autofs_info *ino = autofs4_dentry_ino(dentry);
	struct autofs_info *p_ino;
	struct inode *inode;

	if (!autofs4_oz_mode(sbi))
		return -EACCES;

	DPRINTK("dentry %p, creating %.*s",
		dentry, dentry->d_name.len, dentry->d_name.name);

	ino = autofs4_init_ino(ino, sbi, S_IFDIR | 0555);
	if (!ino)
		return -ENOMEM;

	autofs4_del_active(dentry);

	inode = autofs4_get_inode(dir->i_sb, ino);
	if (!inode) {
		if (!dentry->d_fsdata)
			kfree(ino);
		return -ENOMEM;
	}
	d_add(dentry, inode);

	if (sbi->version < 5)
		autofs_set_leaf_automount_flags(dentry);

	dentry->d_fsdata = ino;
	ino->dentry = dget(dentry);
	atomic_inc(&ino->count);
	p_ino = autofs4_dentry_ino(dentry->d_parent);
	if (p_ino && dentry->d_parent != dentry)
		atomic_inc(&p_ino->count);
	inc_nlink(dir);
	dir->i_mtime = CURRENT_TIME;

	return 0;
}