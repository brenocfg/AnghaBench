#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_flags; } ;
struct ext4_sb_info {int s_groups_count; TYPE_1__* s_es; int /*<<< orphan*/  s_itb_per_group; } ;
struct ext4_group_desc {int bg_flags; int /*<<< orphan*/  bg_checksum; } ;
typedef  int ext4_group_t ;
typedef  int ext4_fsblk_t ;
struct TYPE_3__ {int /*<<< orphan*/  s_free_inodes_count; int /*<<< orphan*/  s_first_data_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_BG_INODE_ZEROED ; 
 int EXT4_BLOCKS_PER_GROUP (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_FEATURE_INCOMPAT_FLEX_BG ; 
 scalar_t__ EXT4_HAS_INCOMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int MS_RDONLY ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int ext4_block_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 int ext4_blocks_count (TYPE_1__*) ; 
 int /*<<< orphan*/  ext4_count_free_blocks (struct super_block*) ; 
 int /*<<< orphan*/  ext4_count_free_inodes (struct super_block*) ; 
 int /*<<< orphan*/  ext4_debug (char*) ; 
 int /*<<< orphan*/  ext4_free_blocks_count_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_group_desc_csum (struct ext4_sb_info*,int,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_group_desc_csum_verify (struct ext4_sb_info*,int,struct ext4_group_desc*) ; 
 int ext4_inode_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 int ext4_inode_table (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_lock_group (struct super_block*,int) ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  ext4_unlock_group (struct super_block*,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_check_descriptors(struct super_block *sb,
				  ext4_group_t *first_not_zeroed)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_fsblk_t first_block = le32_to_cpu(sbi->s_es->s_first_data_block);
	ext4_fsblk_t last_block;
	ext4_fsblk_t block_bitmap;
	ext4_fsblk_t inode_bitmap;
	ext4_fsblk_t inode_table;
	int flexbg_flag = 0;
	ext4_group_t i, grp = sbi->s_groups_count;

	if (EXT4_HAS_INCOMPAT_FEATURE(sb, EXT4_FEATURE_INCOMPAT_FLEX_BG))
		flexbg_flag = 1;

	ext4_debug("Checking group descriptors");

	for (i = 0; i < sbi->s_groups_count; i++) {
		struct ext4_group_desc *gdp = ext4_get_group_desc(sb, i, NULL);

		if (i == sbi->s_groups_count - 1 || flexbg_flag)
			last_block = ext4_blocks_count(sbi->s_es) - 1;
		else
			last_block = first_block +
				(EXT4_BLOCKS_PER_GROUP(sb) - 1);

		if ((grp == sbi->s_groups_count) &&
		   !(gdp->bg_flags & cpu_to_le16(EXT4_BG_INODE_ZEROED)))
			grp = i;

		block_bitmap = ext4_block_bitmap(sb, gdp);
		if (block_bitmap < first_block || block_bitmap > last_block) {
			ext4_msg(sb, KERN_ERR, "ext4_check_descriptors: "
			       "Block bitmap for group %u not in group "
			       "(block %llu)!", i, block_bitmap);
			return 0;
		}
		inode_bitmap = ext4_inode_bitmap(sb, gdp);
		if (inode_bitmap < first_block || inode_bitmap > last_block) {
			ext4_msg(sb, KERN_ERR, "ext4_check_descriptors: "
			       "Inode bitmap for group %u not in group "
			       "(block %llu)!", i, inode_bitmap);
			return 0;
		}
		inode_table = ext4_inode_table(sb, gdp);
		if (inode_table < first_block ||
		    inode_table + sbi->s_itb_per_group - 1 > last_block) {
			ext4_msg(sb, KERN_ERR, "ext4_check_descriptors: "
			       "Inode table for group %u not in group "
			       "(block %llu)!", i, inode_table);
			return 0;
		}
		ext4_lock_group(sb, i);
		if (!ext4_group_desc_csum_verify(sbi, i, gdp)) {
			ext4_msg(sb, KERN_ERR, "ext4_check_descriptors: "
				 "Checksum for group %u failed (%u!=%u)",
				 i, le16_to_cpu(ext4_group_desc_csum(sbi, i,
				     gdp)), le16_to_cpu(gdp->bg_checksum));
			if (!(sb->s_flags & MS_RDONLY)) {
				ext4_unlock_group(sb, i);
				return 0;
			}
		}
		ext4_unlock_group(sb, i);
		if (!flexbg_flag)
			first_block += EXT4_BLOCKS_PER_GROUP(sb);
	}
	if (NULL != first_not_zeroed)
		*first_not_zeroed = grp;

	ext4_free_blocks_count_set(sbi->s_es, ext4_count_free_blocks(sb));
	sbi->s_es->s_free_inodes_count =cpu_to_le32(ext4_count_free_inodes(sb));
	return 1;
}