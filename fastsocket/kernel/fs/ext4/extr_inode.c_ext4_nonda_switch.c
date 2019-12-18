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
struct super_block {int dummy; } ;
struct ext4_sb_info {int /*<<< orphan*/  s_dirtyblocks_counter; int /*<<< orphan*/  s_freeblocks_counter; } ;
typedef  int s64 ;

/* Variables and functions */
 int EXT4_FREEBLOCKS_WATERMARK ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int percpu_counter_read_positive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeback_inodes_sb_if_idle (struct super_block*) ; 

__attribute__((used)) static int ext4_nonda_switch(struct super_block *sb)
{
	s64 free_blocks, dirty_blocks;
	struct ext4_sb_info *sbi = EXT4_SB(sb);

	/*
	 * switch to non delalloc mode if we are running low
	 * on free block. The free block accounting via percpu
	 * counters can get slightly wrong with percpu_counter_batch getting
	 * accumulated on each CPU without updating global counters
	 * Delalloc need an accurate free block accounting. So switch
	 * to non delalloc when we are near to error range.
	 */
	free_blocks  = percpu_counter_read_positive(&sbi->s_freeblocks_counter);
	dirty_blocks = percpu_counter_read_positive(&sbi->s_dirtyblocks_counter);
	if (2 * free_blocks < 3 * dirty_blocks ||
		free_blocks < (dirty_blocks + EXT4_FREEBLOCKS_WATERMARK)) {
		/*
		 * free block count is less than 150% of dirty blocks
		 * or free blocks is less than watermark
		 */
		return 1;
	}
	/*
	 * Even if we don't switch but are nearing capacity,
	 * start pushing delalloc when 1/2 of free blocks are dirty.
	 */
	if (free_blocks < 2 * dirty_blocks)
		writeback_inodes_sb_if_idle(sb);

	return 0;
}