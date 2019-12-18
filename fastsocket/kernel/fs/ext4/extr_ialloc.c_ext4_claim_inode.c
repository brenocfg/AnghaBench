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
struct ext4_sb_info {TYPE_1__* s_flex_groups; scalar_t__ s_log_groups_per_flex; } ;
struct ext4_group_info {int /*<<< orphan*/  alloc_sem; } ;
struct ext4_group_desc {int bg_flags; int /*<<< orphan*/  bg_checksum; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  unsigned long ext4_group_t ;
struct TYPE_2__ {int /*<<< orphan*/  used_dirs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_BG_INODE_UNINIT ; 
 int /*<<< orphan*/  EXT4_FEATURE_RO_COMPAT_GDT_CSUM ; 
 unsigned long EXT4_FIRST_INO (struct super_block*) ; 
 scalar_t__ EXT4_HAS_RO_COMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 unsigned long EXT4_INODES_PER_GROUP (struct super_block*) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 scalar_t__ S_ISDIR (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_error (struct super_block*,char*,unsigned long,unsigned long) ; 
 unsigned long ext4_flex_group (struct ext4_sb_info*,unsigned long) ; 
 int ext4_free_inodes_count (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_free_inodes_set (struct super_block*,struct ext4_group_desc*,int) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,unsigned long,int /*<<< orphan*/ *) ; 
 struct ext4_group_info* ext4_get_group_info (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  ext4_group_desc_csum (struct ext4_sb_info*,unsigned long,struct ext4_group_desc*) ; 
 unsigned long ext4_itable_unused_count (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_itable_unused_set (struct super_block*,struct ext4_group_desc*,unsigned long) ; 
 int /*<<< orphan*/  ext4_lock_group (struct super_block*,unsigned long) ; 
 scalar_t__ ext4_set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_unlock_group (struct super_block*,unsigned long) ; 
 int ext4_used_dirs_count (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_used_dirs_set (struct super_block*,struct ext4_group_desc*,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext4_claim_inode(struct super_block *sb,
			struct buffer_head *inode_bitmap_bh,
			unsigned long ino, ext4_group_t group, int mode)
{
	int free = 0, retval = 0, count;
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct ext4_group_info *grp = ext4_get_group_info(sb, group);
	struct ext4_group_desc *gdp = ext4_get_group_desc(sb, group, NULL);

	/*
	 * We have to be sure that new inode allocation does not race with
	 * inode table initialization, because otherwise we may end up
	 * allocating and writing new inode right before sb_issue_zeroout
	 * takes place and overwriting our new inode with zeroes. So we
	 * take alloc_sem to prevent it.
	 */
	down_read(&grp->alloc_sem);
	ext4_lock_group(sb, group);
	if (ext4_set_bit(ino, inode_bitmap_bh->b_data)) {
		/* not a free inode */
		retval = 1;
		goto err_ret;
	}
	ino++;
	if ((group == 0 && ino < EXT4_FIRST_INO(sb)) ||
			ino > EXT4_INODES_PER_GROUP(sb)) {
		ext4_unlock_group(sb, group);
		up_read(&grp->alloc_sem);
		ext4_error(sb, "reserved inode or inode > inodes count - "
			   "block_group = %u, inode=%lu", group,
			   ino + group * EXT4_INODES_PER_GROUP(sb));
		return 1;
	}
	/* If we didn't allocate from within the initialized part of the inode
	 * table then we need to initialize up to this inode. */
	if (EXT4_HAS_RO_COMPAT_FEATURE(sb, EXT4_FEATURE_RO_COMPAT_GDT_CSUM)) {

		if (gdp->bg_flags & cpu_to_le16(EXT4_BG_INODE_UNINIT)) {
			gdp->bg_flags &= cpu_to_le16(~EXT4_BG_INODE_UNINIT);
			/* When marking the block group with
			 * ~EXT4_BG_INODE_UNINIT we don't want to depend
			 * on the value of bg_itable_unused even though
			 * mke2fs could have initialized the same for us.
			 * Instead we calculated the value below
			 */

			free = 0;
		} else {
			free = EXT4_INODES_PER_GROUP(sb) -
				ext4_itable_unused_count(sb, gdp);
		}

		/*
		 * Check the relative inode number against the last used
		 * relative inode number in this group. if it is greater
		 * we need to  update the bg_itable_unused count
		 *
		 */
		if (ino > free)
			ext4_itable_unused_set(sb, gdp,
					(EXT4_INODES_PER_GROUP(sb) - ino));
	}
	count = ext4_free_inodes_count(sb, gdp) - 1;
	ext4_free_inodes_set(sb, gdp, count);
	if (S_ISDIR(mode)) {
		count = ext4_used_dirs_count(sb, gdp) + 1;
		ext4_used_dirs_set(sb, gdp, count);
		if (sbi->s_log_groups_per_flex) {
			ext4_group_t f = ext4_flex_group(sbi, group);

			atomic_inc(&sbi->s_flex_groups[f].used_dirs);
		}
	}
	gdp->bg_checksum = ext4_group_desc_csum(sbi, group, gdp);
err_ret:
	ext4_unlock_group(sb, group);
	up_read(&grp->alloc_sem);
	return retval;
}