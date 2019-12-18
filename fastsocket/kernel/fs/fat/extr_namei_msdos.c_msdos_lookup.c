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
struct super_block {int dummy; } ;
struct nameidata {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct fat_slot_info {int /*<<< orphan*/  bh; int /*<<< orphan*/  i_pos; int /*<<< orphan*/  de; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/ * d_op; TYPE_1__ d_name; } ;

/* Variables and functions */
 int ENOENT ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 struct inode* fat_build_inode (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_super (struct super_block*) ; 
 int /*<<< orphan*/  msdos_dentry_operations ; 
 int msdos_find (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fat_slot_info*) ; 
 int /*<<< orphan*/  unlock_super (struct super_block*) ; 

__attribute__((used)) static struct dentry *msdos_lookup(struct inode *dir, struct dentry *dentry,
				   struct nameidata *nd)
{
	struct super_block *sb = dir->i_sb;
	struct fat_slot_info sinfo;
	struct inode *inode;
	int err;

	lock_super(sb);

	err = msdos_find(dir, dentry->d_name.name, dentry->d_name.len, &sinfo);
	if (err) {
		if (err == -ENOENT) {
			inode = NULL;
			goto out;
		}
		goto error;
	}

	inode = fat_build_inode(sb, sinfo.de, sinfo.i_pos);
	brelse(sinfo.bh);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto error;
	}
out:
	unlock_super(sb);
	dentry->d_op = &msdos_dentry_operations;
	dentry = d_splice_alias(inode, dentry);
	if (dentry)
		dentry->d_op = &msdos_dentry_operations;
	return dentry;

error:
	unlock_super(sb);
	return ERR_PTR(err);
}