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
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct ext4_sb_info {int /*<<< orphan*/  s_dirtyblocks_counter; } ;
struct ext4_inode_info {int i_reserved_data_blocks; int i_reserved_meta_blocks; int /*<<< orphan*/  i_block_reservation_lock; scalar_t__ i_da_metadata_calc_len; } ;

/* Variables and functions */
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ext4_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  percpu_counter_sub (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vfs_dq_release_reservation_block (struct inode*,int) ; 

__attribute__((used)) static void ext4_da_release_space(struct inode *inode, int to_free)
{
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	struct ext4_inode_info *ei = EXT4_I(inode);

	if (!to_free)
		return;		/* Nothing to release, exit */

	spin_lock(&EXT4_I(inode)->i_block_reservation_lock);

	if (unlikely(to_free > ei->i_reserved_data_blocks)) {
		/*
		 * if there aren't enough reserved blocks, then the
		 * counter is messed up somewhere.  Since this
		 * function is called from invalidate page, it's
		 * harmless to return without any action.
		 */
		ext4_msg(inode->i_sb, KERN_NOTICE, "ext4_da_release_space: "
			 "ino %lu, to_free %d with only %d reserved "
			 "data blocks\n", inode->i_ino, to_free,
			 ei->i_reserved_data_blocks);
		WARN_ON(1);
		to_free = ei->i_reserved_data_blocks;
	}
	ei->i_reserved_data_blocks -= to_free;

	if (ei->i_reserved_data_blocks == 0) {
		/*
		 * We can release all of the reserved metadata blocks
		 * only when we have written all of the delayed
		 * allocation blocks.
		 */
		percpu_counter_sub(&sbi->s_dirtyblocks_counter,
				   ei->i_reserved_meta_blocks);
		ei->i_reserved_meta_blocks = 0;
		ei->i_da_metadata_calc_len = 0;
	}

	/* update fs dirty data blocks counter */
	percpu_counter_sub(&sbi->s_dirtyblocks_counter, to_free);

	spin_unlock(&EXT4_I(inode)->i_block_reservation_lock);

	vfs_dq_release_reservation_block(inode, to_free);
}