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
struct ubifs_inode {scalar_t__ dirty; scalar_t__ ui_size; scalar_t__ xattr; } ;
struct ubifs_info {scalar_t__ nospace_rp; scalar_t__ nospace; } ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_ino; scalar_t__ i_size; int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_count; scalar_t__ i_mode; TYPE_1__* i_sb; } ;
struct TYPE_2__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_err (char*,int /*<<< orphan*/ ,int) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int ubifs_jnl_delete_inode (struct ubifs_info*,struct inode*) ; 
 int /*<<< orphan*/  ubifs_release_dirty_inode_budget (struct ubifs_info*,struct ubifs_inode*) ; 

__attribute__((used)) static void ubifs_delete_inode(struct inode *inode)
{
	int err;
	struct ubifs_info *c = inode->i_sb->s_fs_info;
	struct ubifs_inode *ui = ubifs_inode(inode);

	if (ui->xattr)
		/*
		 * Extended attribute inode deletions are fully handled in
		 * 'ubifs_removexattr()'. These inodes are special and have
		 * limited usage, so there is nothing to do here.
		 */
		goto out;

	dbg_gen("inode %lu, mode %#x", inode->i_ino, (int)inode->i_mode);
	ubifs_assert(!atomic_read(&inode->i_count));
	ubifs_assert(inode->i_nlink == 0);

	truncate_inode_pages(&inode->i_data, 0);
	if (is_bad_inode(inode))
		goto out;

	ui->ui_size = inode->i_size = 0;
	err = ubifs_jnl_delete_inode(c, inode);
	if (err)
		/*
		 * Worst case we have a lost orphan inode wasting space, so a
		 * simple error message is OK here.
		 */
		ubifs_err("can't delete inode %lu, error %d",
			  inode->i_ino, err);

out:
	if (ui->dirty)
		ubifs_release_dirty_inode_budget(c, ui);
	else {
		/* We've deleted something - clean the "no space" flags */
		c->nospace = c->nospace_rp = 0;
		smp_wmb();
	}
	clear_inode(inode);
}