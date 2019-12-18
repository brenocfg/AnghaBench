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
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct orlov_stats {unsigned int free_inodes; int used_dirs; int free_blocks; } ;
struct inode {int dummy; } ;
struct ext4_sb_info {int s_log_groups_per_flex; int /*<<< orphan*/  s_hash_seed; int /*<<< orphan*/  s_dirs_counter; int /*<<< orphan*/  s_freeblocks_counter; int /*<<< orphan*/  s_freeinodes_counter; } ;
struct ext4_group_desc {int dummy; } ;
struct dx_hash_info {int hash; int /*<<< orphan*/  seed; int /*<<< orphan*/  hash_version; } ;
typedef  int /*<<< orphan*/  grp ;
typedef  int ext4_grpblk_t ;
typedef  int ext4_group_t ;
typedef  int ext4_fsblk_t ;
struct TYPE_4__ {int i_block_group; int i_last_alloc_group; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DX_HASH_HALF_MD4 ; 
 int EXT4_BLOCKS_PER_GROUP (struct super_block*) ; 
 TYPE_2__* EXT4_I (struct inode*) ; 
 int EXT4_INODES_PER_GROUP (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_INODE_TOPDIR ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 scalar_t__ S_ISDIR (int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int ext4_flex_bg_size (struct ext4_sb_info*) ; 
 unsigned int ext4_free_inodes_count (struct super_block*,struct ext4_group_desc*) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,int,int /*<<< orphan*/ *) ; 
 int ext4_get_groups_count (struct super_block*) ; 
 scalar_t__ ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4fs_dirhash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dx_hash_info*) ; 
 int /*<<< orphan*/  get_orlov_stats (struct super_block*,int,int,struct orlov_stats*) ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 void* percpu_counter_read_positive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int find_group_orlov(struct super_block *sb, struct inode *parent,
			    ext4_group_t *group, int mode,
			    const struct qstr *qstr)
{
	ext4_group_t parent_group = EXT4_I(parent)->i_block_group;
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_group_t real_ngroups = ext4_get_groups_count(sb);
	int inodes_per_group = EXT4_INODES_PER_GROUP(sb);
	unsigned int freei, avefreei;
	ext4_fsblk_t freeb, avefreeb;
	unsigned int ndirs;
	int max_dirs, min_inodes;
	ext4_grpblk_t min_blocks;
	ext4_group_t i, grp, g, ngroups;
	struct ext4_group_desc *desc;
	struct orlov_stats stats;
	int flex_size = ext4_flex_bg_size(sbi);
	struct dx_hash_info hinfo;

	ngroups = real_ngroups;
	if (flex_size > 1) {
		ngroups = (real_ngroups + flex_size - 1) >>
			sbi->s_log_groups_per_flex;
		parent_group >>= sbi->s_log_groups_per_flex;
	}

	freei = percpu_counter_read_positive(&sbi->s_freeinodes_counter);
	avefreei = freei / ngroups;
	freeb = percpu_counter_read_positive(&sbi->s_freeblocks_counter);
	avefreeb = freeb;
	do_div(avefreeb, ngroups);
	ndirs = percpu_counter_read_positive(&sbi->s_dirs_counter);

	if (S_ISDIR(mode) &&
	    ((parent == sb->s_root->d_inode) ||
	     (ext4_test_inode_flag(parent, EXT4_INODE_TOPDIR)))) {
		int best_ndir = inodes_per_group;
		int ret = -1;

		if (qstr) {
			hinfo.hash_version = DX_HASH_HALF_MD4;
			hinfo.seed = sbi->s_hash_seed;
			ext4fs_dirhash(qstr->name, qstr->len, &hinfo);
			grp = hinfo.hash;
		} else
			get_random_bytes(&grp, sizeof(grp));
		parent_group = (unsigned)grp % ngroups;
		for (i = 0; i < ngroups; i++) {
			g = (parent_group + i) % ngroups;
			get_orlov_stats(sb, g, flex_size, &stats);
			if (!stats.free_inodes)
				continue;
			if (stats.used_dirs >= best_ndir)
				continue;
			if (stats.free_inodes < avefreei)
				continue;
			if (stats.free_blocks < avefreeb)
				continue;
			grp = g;
			ret = 0;
			best_ndir = stats.used_dirs;
		}
		if (ret)
			goto fallback;
	found_flex_bg:
		if (flex_size == 1) {
			*group = grp;
			return 0;
		}

		/*
		 * We pack inodes at the beginning of the flexgroup's
		 * inode tables.  Block allocation decisions will do
		 * something similar, although regular files will
		 * start at 2nd block group of the flexgroup.  See
		 * ext4_ext_find_goal() and ext4_find_near().
		 */
		grp *= flex_size;
		for (i = 0; i < flex_size; i++) {
			if (grp+i >= real_ngroups)
				break;
			desc = ext4_get_group_desc(sb, grp+i, NULL);
			if (desc && ext4_free_inodes_count(sb, desc)) {
				*group = grp+i;
				return 0;
			}
		}
		goto fallback;
	}

	max_dirs = ndirs / ngroups + inodes_per_group / 16;
	min_inodes = avefreei - inodes_per_group*flex_size / 4;
	if (min_inodes < 1)
		min_inodes = 1;
	min_blocks = avefreeb - EXT4_BLOCKS_PER_GROUP(sb)*flex_size / 4;

	/*
	 * Start looking in the flex group where we last allocated an
	 * inode for this parent directory
	 */
	if (EXT4_I(parent)->i_last_alloc_group != ~0) {
		parent_group = EXT4_I(parent)->i_last_alloc_group;
		if (flex_size > 1)
			parent_group >>= sbi->s_log_groups_per_flex;
	}

	for (i = 0; i < ngroups; i++) {
		grp = (parent_group + i) % ngroups;
		get_orlov_stats(sb, grp, flex_size, &stats);
		if (stats.used_dirs >= max_dirs)
			continue;
		if (stats.free_inodes < min_inodes)
			continue;
		if (stats.free_blocks < min_blocks)
			continue;
		goto found_flex_bg;
	}

fallback:
	ngroups = real_ngroups;
	avefreei = freei / ngroups;
fallback_retry:
	parent_group = EXT4_I(parent)->i_block_group;
	for (i = 0; i < ngroups; i++) {
		grp = (parent_group + i) % ngroups;
		desc = ext4_get_group_desc(sb, grp, NULL);
		if (desc && ext4_free_inodes_count(sb, desc) &&
		    ext4_free_inodes_count(sb, desc) >= avefreei) {
			*group = grp;
			return 0;
		}
	}

	if (avefreei) {
		/*
		 * The free-inodes counter is approximate, and for really small
		 * filesystems the above test can fail to find any blockgroups
		 */
		avefreei = 0;
		goto fallback_retry;
	}

	return -1;
}