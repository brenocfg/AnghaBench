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
typedef  int u32 ;
struct super_block {int dummy; } ;
struct ext4_group_desc {void* bg_block_bitmap_hi; void* bg_block_bitmap_lo; } ;
typedef  int ext4_fsblk_t ;

/* Variables and functions */
 scalar_t__ EXT4_DESC_SIZE (struct super_block*) ; 
 scalar_t__ EXT4_MIN_DESC_SIZE_64BIT ; 
 void* cpu_to_le32 (int) ; 

void ext4_block_bitmap_set(struct super_block *sb,
			   struct ext4_group_desc *bg, ext4_fsblk_t blk)
{
	bg->bg_block_bitmap_lo = cpu_to_le32((u32)blk);
	if (EXT4_DESC_SIZE(sb) >= EXT4_MIN_DESC_SIZE_64BIT)
		bg->bg_block_bitmap_hi = cpu_to_le32(blk >> 32);
}