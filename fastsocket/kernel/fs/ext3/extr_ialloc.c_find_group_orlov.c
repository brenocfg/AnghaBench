#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_1__* s_root; } ;
struct inode {int dummy; } ;
struct ext3_super_block {int /*<<< orphan*/  s_blocks_count; } ;
struct ext3_sb_info {int s_groups_count; int /*<<< orphan*/  s_dirs_counter; int /*<<< orphan*/  s_freeblocks_counter; int /*<<< orphan*/  s_freeinodes_counter; struct ext3_super_block* s_es; } ;
struct ext3_group_desc {int /*<<< orphan*/  bg_free_inodes_count; int /*<<< orphan*/  bg_free_blocks_count; int /*<<< orphan*/  bg_used_dirs_count; } ;
typedef  int /*<<< orphan*/  group ;
typedef  unsigned int ext3_grpblk_t ;
typedef  int ext3_fsblk_t ;
struct TYPE_4__ {int i_block_group; int i_flags; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 scalar_t__ BLOCK_COST ; 
 int EXT3_BLOCKS_PER_GROUP (struct super_block*) ; 
 TYPE_2__* EXT3_I (struct inode*) ; 
 int EXT3_INODES_PER_GROUP (struct super_block*) ; 
 struct ext3_sb_info* EXT3_SB (struct super_block*) ; 
 int EXT3_TOPDIR_FL ; 
 int INODE_COST ; 
 struct ext3_group_desc* ext3_get_group_desc (struct super_block*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 void* percpu_counter_read_positive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int find_group_orlov(struct super_block *sb, struct inode *parent)
{
	int parent_group = EXT3_I(parent)->i_block_group;
	struct ext3_sb_info *sbi = EXT3_SB(sb);
	struct ext3_super_block *es = sbi->s_es;
	int ngroups = sbi->s_groups_count;
	int inodes_per_group = EXT3_INODES_PER_GROUP(sb);
	unsigned int freei, avefreei;
	ext3_fsblk_t freeb, avefreeb;
	ext3_fsblk_t blocks_per_dir;
	unsigned int ndirs;
	int max_debt, max_dirs, min_inodes;
	ext3_grpblk_t min_blocks;
	int group = -1, i;
	struct ext3_group_desc *desc;

	freei = percpu_counter_read_positive(&sbi->s_freeinodes_counter);
	avefreei = freei / ngroups;
	freeb = percpu_counter_read_positive(&sbi->s_freeblocks_counter);
	avefreeb = freeb / ngroups;
	ndirs = percpu_counter_read_positive(&sbi->s_dirs_counter);

	if ((parent == sb->s_root->d_inode) ||
	    (EXT3_I(parent)->i_flags & EXT3_TOPDIR_FL)) {
		int best_ndir = inodes_per_group;
		int best_group = -1;

		get_random_bytes(&group, sizeof(group));
		parent_group = (unsigned)group % ngroups;
		for (i = 0; i < ngroups; i++) {
			group = (parent_group + i) % ngroups;
			desc = ext3_get_group_desc (sb, group, NULL);
			if (!desc || !desc->bg_free_inodes_count)
				continue;
			if (le16_to_cpu(desc->bg_used_dirs_count) >= best_ndir)
				continue;
			if (le16_to_cpu(desc->bg_free_inodes_count) < avefreei)
				continue;
			if (le16_to_cpu(desc->bg_free_blocks_count) < avefreeb)
				continue;
			best_group = group;
			best_ndir = le16_to_cpu(desc->bg_used_dirs_count);
		}
		if (best_group >= 0)
			return best_group;
		goto fallback;
	}

	blocks_per_dir = (le32_to_cpu(es->s_blocks_count) - freeb) / ndirs;

	max_dirs = ndirs / ngroups + inodes_per_group / 16;
	min_inodes = avefreei - inodes_per_group / 4;
	min_blocks = avefreeb - EXT3_BLOCKS_PER_GROUP(sb) / 4;

	max_debt = EXT3_BLOCKS_PER_GROUP(sb) / max(blocks_per_dir, (ext3_fsblk_t)BLOCK_COST);
	if (max_debt * INODE_COST > inodes_per_group)
		max_debt = inodes_per_group / INODE_COST;
	if (max_debt > 255)
		max_debt = 255;
	if (max_debt == 0)
		max_debt = 1;

	for (i = 0; i < ngroups; i++) {
		group = (parent_group + i) % ngroups;
		desc = ext3_get_group_desc (sb, group, NULL);
		if (!desc || !desc->bg_free_inodes_count)
			continue;
		if (le16_to_cpu(desc->bg_used_dirs_count) >= max_dirs)
			continue;
		if (le16_to_cpu(desc->bg_free_inodes_count) < min_inodes)
			continue;
		if (le16_to_cpu(desc->bg_free_blocks_count) < min_blocks)
			continue;
		return group;
	}

fallback:
	for (i = 0; i < ngroups; i++) {
		group = (parent_group + i) % ngroups;
		desc = ext3_get_group_desc (sb, group, NULL);
		if (!desc || !desc->bg_free_inodes_count)
			continue;
		if (le16_to_cpu(desc->bg_free_inodes_count) >= avefreei)
			return group;
	}

	if (avefreei) {
		/*
		 * The free-inodes counter is approximate, and for really small
		 * filesystems the above test can fail to find any blockgroups
		 */
		avefreei = 0;
		goto fallback;
	}

	return -1;
}