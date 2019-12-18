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
struct ext2_super_block {int dummy; } ;
struct ext2_group_desc {int /*<<< orphan*/  bg_free_inodes_count; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int s_groups_count; int /*<<< orphan*/  s_freeinodes_counter; struct ext2_super_block* s_es; } ;

/* Variables and functions */
 int EXT2_INODES_PER_GROUP (struct super_block*) ; 
 TYPE_1__* EXT2_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 unsigned int ext2_count_free (struct buffer_head*,int) ; 
 struct ext2_group_desc* ext2_get_group_desc (struct super_block*,int,int /*<<< orphan*/ *) ; 
 unsigned long le16_to_cpu (int /*<<< orphan*/ ) ; 
 int percpu_counter_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int,unsigned long,unsigned long) ; 
 struct buffer_head* read_inode_bitmap (struct super_block*,int) ; 

unsigned long ext2_count_free_inodes (struct super_block * sb)
{
	struct ext2_group_desc *desc;
	unsigned long desc_count = 0;
	int i;	

#ifdef EXT2FS_DEBUG
	struct ext2_super_block *es;
	unsigned long bitmap_count = 0;
	struct buffer_head *bitmap_bh = NULL;

	es = EXT2_SB(sb)->s_es;
	for (i = 0; i < EXT2_SB(sb)->s_groups_count; i++) {
		unsigned x;

		desc = ext2_get_group_desc (sb, i, NULL);
		if (!desc)
			continue;
		desc_count += le16_to_cpu(desc->bg_free_inodes_count);
		brelse(bitmap_bh);
		bitmap_bh = read_inode_bitmap(sb, i);
		if (!bitmap_bh)
			continue;

		x = ext2_count_free(bitmap_bh, EXT2_INODES_PER_GROUP(sb) / 8);
		printk("group %d: stored = %d, counted = %u\n",
			i, le16_to_cpu(desc->bg_free_inodes_count), x);
		bitmap_count += x;
	}
	brelse(bitmap_bh);
	printk("ext2_count_free_inodes: stored = %lu, computed = %lu, %lu\n",
		percpu_counter_read(&EXT2_SB(sb)->s_freeinodes_counter),
		desc_count, bitmap_count);
	return desc_count;
#else
	for (i = 0; i < EXT2_SB(sb)->s_groups_count; i++) {
		desc = ext2_get_group_desc (sb, i, NULL);
		if (!desc)
			continue;
		desc_count += le16_to_cpu(desc->bg_free_inodes_count);
	}
	return desc_count;
#endif
}