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
struct inode {int dummy; } ;
struct flex_groups {int /*<<< orphan*/  free_blocks; int /*<<< orphan*/  free_inodes; } ;
struct ext4_sb_info {int s_blocks_per_group; int s_log_groups_per_flex; struct flex_groups* s_flex_groups; } ;
struct ext4_group_desc {int dummy; } ;
typedef  int ext4_group_t ;
struct TYPE_2__ {int i_block_group; } ;

/* Variables and functions */
 TYPE_1__* EXT4_I (struct inode*) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int ext4_flex_bg_size (struct ext4_sb_info*) ; 
 int ext4_flex_group (struct ext4_sb_info*,int) ; 
 scalar_t__ ext4_free_inodes_count (struct super_block*,struct ext4_group_desc*) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,int,int /*<<< orphan*/ *) ; 
 int ext4_get_groups_count (struct super_block*) ; 
 int free_block_ratio ; 

__attribute__((used)) static int find_group_flex(struct super_block *sb, struct inode *parent,
			   ext4_group_t *best_group)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct ext4_group_desc *desc;
	struct flex_groups *flex_group = sbi->s_flex_groups;
	ext4_group_t parent_group = EXT4_I(parent)->i_block_group;
	ext4_group_t parent_fbg_group = ext4_flex_group(sbi, parent_group);
	ext4_group_t ngroups = ext4_get_groups_count(sb);
	int flex_size = ext4_flex_bg_size(sbi);
	ext4_group_t best_flex = parent_fbg_group;
	int blocks_per_flex = sbi->s_blocks_per_group * flex_size;
	int flexbg_free_blocks;
	int flex_freeb_ratio;
	ext4_group_t n_fbg_groups;
	ext4_group_t i;

	n_fbg_groups = (ngroups + flex_size - 1) >>
		sbi->s_log_groups_per_flex;

find_close_to_parent:
	flexbg_free_blocks = atomic_read(&flex_group[best_flex].free_blocks);
	flex_freeb_ratio = flexbg_free_blocks * 100 / blocks_per_flex;
	if (atomic_read(&flex_group[best_flex].free_inodes) &&
	    flex_freeb_ratio > free_block_ratio)
		goto found_flexbg;

	if (best_flex && best_flex == parent_fbg_group) {
		best_flex--;
		goto find_close_to_parent;
	}

	for (i = 0; i < n_fbg_groups; i++) {
		if (i == parent_fbg_group || i == parent_fbg_group - 1)
			continue;

		flexbg_free_blocks = atomic_read(&flex_group[i].free_blocks);
		flex_freeb_ratio = flexbg_free_blocks * 100 / blocks_per_flex;

		if (flex_freeb_ratio > free_block_ratio &&
		    (atomic_read(&flex_group[i].free_inodes))) {
			best_flex = i;
			goto found_flexbg;
		}

		if ((atomic_read(&flex_group[best_flex].free_inodes) == 0) ||
		    ((atomic_read(&flex_group[i].free_blocks) >
		      atomic_read(&flex_group[best_flex].free_blocks)) &&
		     atomic_read(&flex_group[i].free_inodes)))
			best_flex = i;
	}

	if (!atomic_read(&flex_group[best_flex].free_inodes) ||
	    !atomic_read(&flex_group[best_flex].free_blocks))
		return -1;

found_flexbg:
	for (i = best_flex * flex_size; i < ngroups &&
		     i < (best_flex + 1) * flex_size; i++) {
		desc = ext4_get_group_desc(sb, i, NULL);
		if (ext4_free_inodes_count(sb, desc)) {
			*best_group = i;
			goto out;
		}
	}

	return -1;
out:
	return 0;
}