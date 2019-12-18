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
struct nilfs_transaction_info {int dummy; } ;
struct nilfs_inode_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ nrpages; } ;
struct inode {TYPE_1__ i_data; struct super_block* i_sb; } ;

/* Variables and functions */
 scalar_t__ IS_SYNC (struct inode*) ; 
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  NILFS_TI_SYNC ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  nilfs_free_inode (struct inode*) ; 
 int /*<<< orphan*/  nilfs_set_transaction_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_transaction_begin (struct super_block*,struct nilfs_transaction_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_transaction_commit (struct super_block*) ; 
 int /*<<< orphan*/  nilfs_truncate_bmap (struct nilfs_inode_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_inode_pages (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void nilfs_delete_inode(struct inode *inode)
{
	struct nilfs_transaction_info ti;
	struct super_block *sb = inode->i_sb;
	struct nilfs_inode_info *ii = NILFS_I(inode);

	if (unlikely(is_bad_inode(inode))) {
		if (inode->i_data.nrpages)
			truncate_inode_pages(&inode->i_data, 0);
		clear_inode(inode);
		return;
	}
	nilfs_transaction_begin(sb, &ti, 0); /* never fails */

	if (inode->i_data.nrpages)
		truncate_inode_pages(&inode->i_data, 0);

	nilfs_truncate_bmap(ii, 0);
	nilfs_free_inode(inode);
	/* nilfs_free_inode() marks inode buffer dirty */
	if (IS_SYNC(inode))
		nilfs_set_transaction_flag(NILFS_TI_SYNC);
	nilfs_transaction_commit(sb);
	/* May construct a logical segment and may fail in sync mode.
	   But delete_inode has no return value. */
}