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
struct super_block {int s_blocksize; } ;
struct ext4_sb_info {int s_desc_per_block; scalar_t__ s_itb_per_group; TYPE_1__* s_es; } ;
struct ext4_group_desc {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_first_data_block; int /*<<< orphan*/  s_reserved_gdt_blocks; int /*<<< orphan*/  s_first_meta_bg; } ;

/* Variables and functions */
 int EXT4_BLOCKS_PER_GROUP (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_FEATURE_INCOMPAT_FLEX_BG ; 
 int /*<<< orphan*/  EXT4_FEATURE_INCOMPAT_META_BG ; 
 scalar_t__ EXT4_HAS_INCOMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  J_ASSERT_BH (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_locked (struct buffer_head*) ; 
 int ext4_bg_has_super (struct super_block*,int) ; 
 scalar_t__ ext4_bg_num_gdb (struct super_block*,int) ; 
 scalar_t__ ext4_block_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 scalar_t__ ext4_block_in_group (struct super_block*,scalar_t__,int) ; 
 int ext4_blocks_count (TYPE_1__*) ; 
 int /*<<< orphan*/  ext4_error (struct super_block*,char*,int) ; 
 int /*<<< orphan*/  ext4_free_blks_set (struct super_block*,struct ext4_group_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_free_inodes_set (struct super_block*,struct ext4_group_desc*,int /*<<< orphan*/ ) ; 
 int ext4_get_groups_count (struct super_block*) ; 
 int /*<<< orphan*/  ext4_group_desc_csum_verify (struct ext4_sb_info*,int,struct ext4_group_desc*) ; 
 scalar_t__ ext4_group_first_block_no (struct super_block*,int) ; 
 int ext4_group_used_meta_blocks (struct super_block*,int,struct ext4_group_desc*) ; 
 scalar_t__ ext4_inode_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 scalar_t__ ext4_inode_table (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_itable_unused_set (struct super_block*,struct ext4_group_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_bitmap_end (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

unsigned ext4_init_block_bitmap(struct super_block *sb, struct buffer_head *bh,
		 ext4_group_t block_group, struct ext4_group_desc *gdp)
{
	int bit, bit_max;
	ext4_group_t ngroups = ext4_get_groups_count(sb);
	unsigned free_blocks, group_blocks;
	struct ext4_sb_info *sbi = EXT4_SB(sb);

	if (bh) {
		J_ASSERT_BH(bh, buffer_locked(bh));

		/* If checksum is bad mark all blocks used to prevent allocation
		 * essentially implementing a per-group read-only flag. */
		if (!ext4_group_desc_csum_verify(sbi, block_group, gdp)) {
			ext4_error(sb, "Checksum bad for group %u",
					block_group);
			ext4_free_blks_set(sb, gdp, 0);
			ext4_free_inodes_set(sb, gdp, 0);
			ext4_itable_unused_set(sb, gdp, 0);
			memset(bh->b_data, 0xff, sb->s_blocksize);
			return 0;
		}
		memset(bh->b_data, 0, sb->s_blocksize);
	}

	/* Check for superblock and gdt backups in this group */
	bit_max = ext4_bg_has_super(sb, block_group);

	if (!EXT4_HAS_INCOMPAT_FEATURE(sb, EXT4_FEATURE_INCOMPAT_META_BG) ||
	    block_group < le32_to_cpu(sbi->s_es->s_first_meta_bg) *
			  sbi->s_desc_per_block) {
		if (bit_max) {
			bit_max += ext4_bg_num_gdb(sb, block_group);
			bit_max +=
				le16_to_cpu(sbi->s_es->s_reserved_gdt_blocks);
		}
	} else { /* For META_BG_BLOCK_GROUPS */
		bit_max += ext4_bg_num_gdb(sb, block_group);
	}

	if (block_group == ngroups - 1) {
		/*
		 * Even though mke2fs always initialize first and last group
		 * if some other tool enabled the EXT4_BG_BLOCK_UNINIT we need
		 * to make sure we calculate the right free blocks
		 */
		group_blocks = ext4_blocks_count(sbi->s_es) -
			le32_to_cpu(sbi->s_es->s_first_data_block) -
			(EXT4_BLOCKS_PER_GROUP(sb) * (ngroups - 1));
	} else {
		group_blocks = EXT4_BLOCKS_PER_GROUP(sb);
	}

	free_blocks = group_blocks - bit_max;

	if (bh) {
		ext4_fsblk_t start, tmp;
		int flex_bg = 0;

		for (bit = 0; bit < bit_max; bit++)
			ext4_set_bit(bit, bh->b_data);

		start = ext4_group_first_block_no(sb, block_group);

		if (EXT4_HAS_INCOMPAT_FEATURE(sb,
					      EXT4_FEATURE_INCOMPAT_FLEX_BG))
			flex_bg = 1;

		/* Set bits for block and inode bitmaps, and inode table */
		tmp = ext4_block_bitmap(sb, gdp);
		if (!flex_bg || ext4_block_in_group(sb, tmp, block_group))
			ext4_set_bit(tmp - start, bh->b_data);

		tmp = ext4_inode_bitmap(sb, gdp);
		if (!flex_bg || ext4_block_in_group(sb, tmp, block_group))
			ext4_set_bit(tmp - start, bh->b_data);

		tmp = ext4_inode_table(sb, gdp);
		for (; tmp < ext4_inode_table(sb, gdp) +
				sbi->s_itb_per_group; tmp++) {
			if (!flex_bg ||
				ext4_block_in_group(sb, tmp, block_group))
				ext4_set_bit(tmp - start, bh->b_data);
		}
		/*
		 * Also if the number of blocks within the group is
		 * less than the blocksize * 8 ( which is the size
		 * of bitmap ), set rest of the block bitmap to 1
		 */
		mark_bitmap_end(group_blocks, sb->s_blocksize * 8, bh->b_data);
	}
	return free_blocks - ext4_group_used_meta_blocks(sb, block_group, gdp);
}