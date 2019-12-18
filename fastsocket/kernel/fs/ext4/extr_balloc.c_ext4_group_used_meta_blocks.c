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
struct super_block {int dummy; } ;
struct ext4_sb_info {int s_itb_per_group; } ;
struct ext4_group_desc {int dummy; } ;
typedef  int /*<<< orphan*/  ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_FEATURE_INCOMPAT_FLEX_BG ; 
 scalar_t__ EXT4_HAS_INCOMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 scalar_t__ ext4_block_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_block_in_group (struct super_block*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_inode_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 scalar_t__ ext4_inode_table (struct super_block*,struct ext4_group_desc*) ; 

__attribute__((used)) static int ext4_group_used_meta_blocks(struct super_block *sb,
				       ext4_group_t block_group,
				       struct ext4_group_desc *gdp)
{
	ext4_fsblk_t tmp;
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	/* block bitmap, inode bitmap, and inode table blocks */
	int used_blocks = sbi->s_itb_per_group + 2;

	if (EXT4_HAS_INCOMPAT_FEATURE(sb, EXT4_FEATURE_INCOMPAT_FLEX_BG)) {
		if (!ext4_block_in_group(sb, ext4_block_bitmap(sb, gdp),
					block_group))
			used_blocks--;

		if (!ext4_block_in_group(sb, ext4_inode_bitmap(sb, gdp),
					block_group))
			used_blocks--;

		tmp = ext4_inode_table(sb, gdp);
		for (; tmp < ext4_inode_table(sb, gdp) +
				sbi->s_itb_per_group; tmp++) {
			if (!ext4_block_in_group(sb, tmp, block_group))
				used_blocks -= 1;
		}
	}
	return used_blocks;
}