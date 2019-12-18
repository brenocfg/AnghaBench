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
struct super_block {TYPE_1__* s_root; } ;
struct msdos_dir_entry {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_op; int /*<<< orphan*/  d_inode; struct super_block* d_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  d_op; } ;

/* Variables and functions */
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct dentry* d_obtain_alias (struct inode*) ; 
 struct inode* fat_build_inode (struct super_block*,struct msdos_dir_entry*,int /*<<< orphan*/ ) ; 
 int fat_get_dotdot_entry (int /*<<< orphan*/ ,struct buffer_head**,struct msdos_dir_entry**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_super (struct super_block*) ; 
 int /*<<< orphan*/  unlock_super (struct super_block*) ; 

__attribute__((used)) static struct dentry *fat_get_parent(struct dentry *child)
{
	struct super_block *sb = child->d_sb;
	struct buffer_head *bh;
	struct msdos_dir_entry *de;
	loff_t i_pos;
	struct dentry *parent;
	struct inode *inode;
	int err;

	lock_super(sb);

	err = fat_get_dotdot_entry(child->d_inode, &bh, &de, &i_pos);
	if (err) {
		parent = ERR_PTR(err);
		goto out;
	}
	inode = fat_build_inode(sb, de, i_pos);
	brelse(bh);

	parent = d_obtain_alias(inode);
	if (!IS_ERR(parent))
		parent->d_op = sb->s_root->d_op;
out:
	unlock_super(sb);

	return parent;
}