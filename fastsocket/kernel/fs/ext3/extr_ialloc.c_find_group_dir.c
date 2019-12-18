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
struct ext3_group_desc {int /*<<< orphan*/  bg_free_blocks_count; int /*<<< orphan*/  bg_free_inodes_count; } ;
struct TYPE_2__ {int s_groups_count; int /*<<< orphan*/  s_freeinodes_counter; } ;

/* Variables and functions */
 TYPE_1__* EXT3_SB (struct super_block*) ; 
 struct ext3_group_desc* ext3_get_group_desc (struct super_block*,int,int /*<<< orphan*/ *) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int percpu_counter_read_positive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int find_group_dir(struct super_block *sb, struct inode *parent)
{
	int ngroups = EXT3_SB(sb)->s_groups_count;
	unsigned int freei, avefreei;
	struct ext3_group_desc *desc, *best_desc = NULL;
	int group, best_group = -1;

	freei = percpu_counter_read_positive(&EXT3_SB(sb)->s_freeinodes_counter);
	avefreei = freei / ngroups;

	for (group = 0; group < ngroups; group++) {
		desc = ext3_get_group_desc (sb, group, NULL);
		if (!desc || !desc->bg_free_inodes_count)
			continue;
		if (le16_to_cpu(desc->bg_free_inodes_count) < avefreei)
			continue;
		if (!best_desc ||
		    (le16_to_cpu(desc->bg_free_blocks_count) >
		     le16_to_cpu(best_desc->bg_free_blocks_count))) {
			best_group = group;
			best_desc = desc;
		}
	}
	return best_group;
}