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
struct ext4_group_desc {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  scalar_t__ ext4_grpblk_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_2__ {scalar_t__ s_itb_per_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_FEATURE_INCOMPAT_FLEX_BG ; 
 scalar_t__ EXT4_HAS_INCOMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 scalar_t__ ext4_block_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_error (struct super_block*,char*,unsigned int,scalar_t__) ; 
 scalar_t__ ext4_find_next_zero_bit (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ ext4_group_first_block_no (struct super_block*,unsigned int) ; 
 scalar_t__ ext4_inode_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 scalar_t__ ext4_inode_table (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_valid_block_bitmap(struct super_block *sb,
					struct ext4_group_desc *desc,
					unsigned int block_group,
					struct buffer_head *bh)
{
	ext4_grpblk_t offset;
	ext4_grpblk_t next_zero_bit;
	ext4_fsblk_t bitmap_blk;
	ext4_fsblk_t group_first_block;

	if (EXT4_HAS_INCOMPAT_FEATURE(sb, EXT4_FEATURE_INCOMPAT_FLEX_BG)) {
		/* with FLEX_BG, the inode/block bitmaps and itable
		 * blocks may not be in the group at all
		 * so the bitmap validation will be skipped for those groups
		 * or it has to also read the block group where the bitmaps
		 * are located to verify they are set.
		 */
		return 1;
	}
	group_first_block = ext4_group_first_block_no(sb, block_group);

	/* check whether block bitmap block number is set */
	bitmap_blk = ext4_block_bitmap(sb, desc);
	offset = bitmap_blk - group_first_block;
	if (!ext4_test_bit(offset, bh->b_data))
		/* bad block bitmap */
		goto err_out;

	/* check whether the inode bitmap block number is set */
	bitmap_blk = ext4_inode_bitmap(sb, desc);
	offset = bitmap_blk - group_first_block;
	if (!ext4_test_bit(offset, bh->b_data))
		/* bad block bitmap */
		goto err_out;

	/* check whether the inode table block number is set */
	bitmap_blk = ext4_inode_table(sb, desc);
	offset = bitmap_blk - group_first_block;
	next_zero_bit = ext4_find_next_zero_bit(bh->b_data,
				offset + EXT4_SB(sb)->s_itb_per_group,
				offset);
	if (next_zero_bit >= offset + EXT4_SB(sb)->s_itb_per_group)
		/* good bitmap for inode tables */
		return 1;

err_out:
	ext4_error(sb, "Invalid block bitmap - block_group = %d, block = %llu",
			block_group, bitmap_blk);
	return 0;
}