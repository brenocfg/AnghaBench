#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_1__* s_root; } ;
struct nameidata {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; struct super_block* i_sb; } ;
struct fat_slot_info {int /*<<< orphan*/  bh; int /*<<< orphan*/  i_pos; int /*<<< orphan*/  de; } ;
struct dentry {int d_flags; TYPE_3__* d_parent; int /*<<< orphan*/  d_time; int /*<<< orphan*/  d_op; int /*<<< orphan*/  d_name; } ;
struct TYPE_6__ {TYPE_2__* d_inode; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_version; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int DCACHE_DISCONNECTED ; 
 int ENOENT ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 struct dentry* d_find_alias (struct inode*) ; 
 int /*<<< orphan*/  d_move (struct dentry*,struct dentry*) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  d_unhashed (struct dentry*) ; 
 struct inode* fat_build_inode (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  lock_super (struct super_block*) ; 
 int /*<<< orphan*/  unlock_super (struct super_block*) ; 
 int vfat_find (struct inode*,int /*<<< orphan*/ *,struct fat_slot_info*) ; 

__attribute__((used)) static struct dentry *vfat_lookup(struct inode *dir, struct dentry *dentry,
				  struct nameidata *nd)
{
	struct super_block *sb = dir->i_sb;
	struct fat_slot_info sinfo;
	struct inode *inode;
	struct dentry *alias;
	int err;

	lock_super(sb);

	err = vfat_find(dir, &dentry->d_name, &sinfo);
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

	alias = d_find_alias(inode);
	if (alias && !(alias->d_flags & DCACHE_DISCONNECTED)) {
		/*
		 * This inode has non DCACHE_DISCONNECTED dentry. This
		 * means, the user did ->lookup() by an another name
		 * (longname vs 8.3 alias of it) in past.
		 *
		 * Switch to new one for reason of locality if possible.
		 */
		BUG_ON(d_unhashed(alias));
		if (!S_ISDIR(inode->i_mode))
			d_move(alias, dentry);
		iput(inode);
		unlock_super(sb);
		return alias;
	}
out:
	unlock_super(sb);
	dentry->d_op = sb->s_root->d_op;
	dentry->d_time = dentry->d_parent->d_inode->i_version;
	dentry = d_splice_alias(inode, dentry);
	if (dentry) {
		dentry->d_op = sb->s_root->d_op;
		dentry->d_time = dentry->d_parent->d_inode->i_version;
	}
	return dentry;

error:
	unlock_super(sb);
	return ERR_PTR(err);
}