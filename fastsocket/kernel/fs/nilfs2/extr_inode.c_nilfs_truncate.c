#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct super_block {unsigned int s_blocksize; unsigned int s_blocksize_bits; } ;
struct nilfs_transaction_info {int dummy; } ;
struct nilfs_inode_info {int /*<<< orphan*/  i_state; } ;
struct inode {unsigned int i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_mapping; struct super_block* i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  NILFS_I_BMAP ; 
 int /*<<< orphan*/  NILFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  NILFS_TI_SYNC ; 
 int /*<<< orphan*/  block_truncate_page (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_get_block ; 
 int /*<<< orphan*/  nilfs_set_file_dirty (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_set_transaction_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_transaction_begin (struct super_block*,struct nilfs_transaction_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_transaction_commit (struct super_block*) ; 
 int /*<<< orphan*/  nilfs_truncate_bmap (struct nilfs_inode_info*,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nilfs_truncate(struct inode *inode)
{
	unsigned long blkoff;
	unsigned int blocksize;
	struct nilfs_transaction_info ti;
	struct super_block *sb = inode->i_sb;
	struct nilfs_inode_info *ii = NILFS_I(inode);

	if (!test_bit(NILFS_I_BMAP, &ii->i_state))
		return;
	if (IS_APPEND(inode) || IS_IMMUTABLE(inode))
		return;

	blocksize = sb->s_blocksize;
	blkoff = (inode->i_size + blocksize - 1) >> sb->s_blocksize_bits;
	nilfs_transaction_begin(sb, &ti, 0); /* never fails */

	block_truncate_page(inode->i_mapping, inode->i_size, nilfs_get_block);

	nilfs_truncate_bmap(ii, blkoff);

	inode->i_mtime = inode->i_ctime = CURRENT_TIME;
	if (IS_SYNC(inode))
		nilfs_set_transaction_flag(NILFS_TI_SYNC);

	nilfs_set_file_dirty(NILFS_SB(sb), inode, 0);
	nilfs_transaction_commit(sb);
	/* May construct a logical segment and may fail in sync mode.
	   But truncate has no return value. */
}