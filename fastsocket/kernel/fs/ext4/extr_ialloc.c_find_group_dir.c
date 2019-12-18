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
struct ext4_group_desc {int dummy; } ;
typedef  unsigned int ext4_group_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_freeinodes_counter; } ;

/* Variables and functions */
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 scalar_t__ ext4_free_blks_count (struct super_block*,struct ext4_group_desc*) ; 
 unsigned int ext4_free_inodes_count (struct super_block*,struct ext4_group_desc*) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,unsigned int,int /*<<< orphan*/ *) ; 
 unsigned int ext4_get_groups_count (struct super_block*) ; 
 unsigned int percpu_counter_read_positive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int find_group_dir(struct super_block *sb, struct inode *parent,
				ext4_group_t *best_group)
{
	ext4_group_t ngroups = ext4_get_groups_count(sb);
	unsigned int freei, avefreei;
	struct ext4_group_desc *desc, *best_desc = NULL;
	ext4_group_t group;
	int ret = -1;

	freei = percpu_counter_read_positive(&EXT4_SB(sb)->s_freeinodes_counter);
	avefreei = freei / ngroups;

	for (group = 0; group < ngroups; group++) {
		desc = ext4_get_group_desc(sb, group, NULL);
		if (!desc || !ext4_free_inodes_count(sb, desc))
			continue;
		if (ext4_free_inodes_count(sb, desc) < avefreei)
			continue;
		if (!best_desc ||
		    (ext4_free_blks_count(sb, desc) >
		     ext4_free_blks_count(sb, best_desc))) {
			*best_group = group;
			best_desc = desc;
			ret = 0;
		}
	}
	return ret;
}