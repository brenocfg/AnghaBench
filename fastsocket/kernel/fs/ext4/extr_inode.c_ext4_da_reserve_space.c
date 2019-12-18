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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_sb_info {int dummy; } ;
struct ext4_inode_info {unsigned long i_reserved_meta_blocks; int /*<<< orphan*/  i_block_reservation_lock; int /*<<< orphan*/  i_reserved_data_blocks; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int EDQUOT ; 
 int ENOSPC ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 unsigned long ext4_calc_metadata_amount (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_claim_free_blocks (struct ext4_sb_info*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_should_retry_alloc (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_dq_release_reservation_block (struct inode*,int) ; 
 scalar_t__ vfs_dq_reserve_block (struct inode*,int) ; 
 int /*<<< orphan*/  yield () ; 

__attribute__((used)) static int ext4_da_reserve_space(struct inode *inode, sector_t lblock)
{
	int retries = 0;
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	struct ext4_inode_info *ei = EXT4_I(inode);
	unsigned long md_needed;

	/*
	 * recalculate the amount of metadata blocks to reserve
	 * in order to allocate nrblocks
	 * worse case is one extent per block
	 */
repeat:
	spin_lock(&ei->i_block_reservation_lock);
	md_needed = ext4_calc_metadata_amount(inode, lblock);
	spin_unlock(&ei->i_block_reservation_lock);

	/*
	 * We will charge metadata quota at writeout time; this saves
	 * us from metadata over-estimation, though we may go over by
	 * a small amount in the end.  Here we just reserve for data.
	 */
	if (vfs_dq_reserve_block(inode, 1))
		return -EDQUOT;

	/*
	 * We do still charge estimated metadata to the sb though;
	 * we cannot afford to run out of free blocks.
	 */
	if (ext4_claim_free_blocks(sbi, md_needed + 1, 0)) {
		vfs_dq_release_reservation_block(inode, 1);
		if (ext4_should_retry_alloc(inode->i_sb, &retries)) {
			yield();
			goto repeat;
		}
		return -ENOSPC;
	}
	spin_lock(&ei->i_block_reservation_lock);
	ei->i_reserved_data_blocks++;
	ei->i_reserved_meta_blocks += md_needed;
	spin_unlock(&ei->i_block_reservation_lock);

	return 0;       /* success */
}