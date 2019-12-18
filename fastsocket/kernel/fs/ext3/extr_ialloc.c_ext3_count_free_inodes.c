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
struct ext3_super_block {int /*<<< orphan*/  s_free_inodes_count; } ;
struct ext3_group_desc {int /*<<< orphan*/  bg_free_inodes_count; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int s_groups_count; struct ext3_super_block* s_es; } ;

/* Variables and functions */
 int EXT3_INODES_PER_GROUP (struct super_block*) ; 
 TYPE_1__* EXT3_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 unsigned long ext3_count_free (struct buffer_head*,int) ; 
 struct ext3_group_desc* ext3_get_group_desc (struct super_block*,int,int /*<<< orphan*/ *) ; 
 unsigned long le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int,unsigned long,unsigned long) ; 
 struct buffer_head* read_inode_bitmap (struct super_block*,int) ; 

unsigned long ext3_count_free_inodes (struct super_block * sb)
{
	unsigned long desc_count;
	struct ext3_group_desc *gdp;
	int i;
#ifdef EXT3FS_DEBUG
	struct ext3_super_block *es;
	unsigned long bitmap_count, x;
	struct buffer_head *bitmap_bh = NULL;

	es = EXT3_SB(sb)->s_es;
	desc_count = 0;
	bitmap_count = 0;
	gdp = NULL;
	for (i = 0; i < EXT3_SB(sb)->s_groups_count; i++) {
		gdp = ext3_get_group_desc (sb, i, NULL);
		if (!gdp)
			continue;
		desc_count += le16_to_cpu(gdp->bg_free_inodes_count);
		brelse(bitmap_bh);
		bitmap_bh = read_inode_bitmap(sb, i);
		if (!bitmap_bh)
			continue;

		x = ext3_count_free(bitmap_bh, EXT3_INODES_PER_GROUP(sb) / 8);
		printk("group %d: stored = %d, counted = %lu\n",
			i, le16_to_cpu(gdp->bg_free_inodes_count), x);
		bitmap_count += x;
	}
	brelse(bitmap_bh);
	printk("ext3_count_free_inodes: stored = %u, computed = %lu, %lu\n",
		le32_to_cpu(es->s_free_inodes_count), desc_count, bitmap_count);
	return desc_count;
#else
	desc_count = 0;
	for (i = 0; i < EXT3_SB(sb)->s_groups_count; i++) {
		gdp = ext3_get_group_desc (sb, i, NULL);
		if (!gdp)
			continue;
		desc_count += le16_to_cpu(gdp->bg_free_inodes_count);
		cond_resched();
	}
	return desc_count;
#endif
}