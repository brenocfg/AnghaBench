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
struct super_block {int s_blocksize; } ;
struct ext4_sb_info {int dummy; } ;
struct ext4_group_desc {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  ext4_group_t ;

/* Variables and functions */
 int EXT4_INODES_PER_GROUP (struct super_block*) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  J_ASSERT_BH (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_locked (struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_error (struct super_block*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_free_blks_set (struct super_block*,struct ext4_group_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_free_inodes_set (struct super_block*,struct ext4_group_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_group_desc_csum_verify (struct ext4_sb_info*,int /*<<< orphan*/ ,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_itable_unused_set (struct super_block*,struct ext4_group_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_bitmap_end (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

unsigned ext4_init_inode_bitmap(struct super_block *sb, struct buffer_head *bh,
				ext4_group_t block_group,
				struct ext4_group_desc *gdp)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);

	J_ASSERT_BH(bh, buffer_locked(bh));

	/* If checksum is bad mark all blocks and inodes use to prevent
	 * allocation, essentially implementing a per-group read-only flag. */
	if (!ext4_group_desc_csum_verify(sbi, block_group, gdp)) {
		ext4_error(sb, "Checksum bad for group %u", block_group);
		ext4_free_blks_set(sb, gdp, 0);
		ext4_free_inodes_set(sb, gdp, 0);
		ext4_itable_unused_set(sb, gdp, 0);
		memset(bh->b_data, 0xff, sb->s_blocksize);
		return 0;
	}

	memset(bh->b_data, 0, (EXT4_INODES_PER_GROUP(sb) + 7) / 8);
	mark_bitmap_end(EXT4_INODES_PER_GROUP(sb), sb->s_blocksize * 8,
			bh->b_data);

	return EXT4_INODES_PER_GROUP(sb);
}