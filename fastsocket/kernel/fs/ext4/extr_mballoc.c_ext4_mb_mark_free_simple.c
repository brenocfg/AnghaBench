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
struct super_block {int s_blocksize_bits; } ;
struct ext4_sb_info {int* s_mb_offsets; } ;
struct ext4_group_info {int /*<<< orphan*/ * bb_counters; } ;
typedef  scalar_t__ ext4_grpblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EXT4_BLOCKS_PER_GROUP (struct super_block*) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 scalar_t__ ffs (scalar_t__) ; 
 scalar_t__ fls (scalar_t__) ; 
 int /*<<< orphan*/  mb_clear_bit (scalar_t__,void*) ; 

__attribute__((used)) static void ext4_mb_mark_free_simple(struct super_block *sb,
				void *buddy, ext4_grpblk_t first, ext4_grpblk_t len,
					struct ext4_group_info *grp)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_grpblk_t min;
	ext4_grpblk_t max;
	ext4_grpblk_t chunk;
	unsigned short border;

	BUG_ON(len > EXT4_BLOCKS_PER_GROUP(sb));

	border = 2 << sb->s_blocksize_bits;

	while (len > 0) {
		/* find how many blocks can be covered since this position */
		max = ffs(first | border) - 1;

		/* find how many blocks of power 2 we need to mark */
		min = fls(len) - 1;

		if (max < min)
			min = max;
		chunk = 1 << min;

		/* mark multiblock chunks only */
		grp->bb_counters[min]++;
		if (min > 0)
			mb_clear_bit(first >> min,
				     buddy + sbi->s_mb_offsets[min]);

		len -= chunk;
		first += chunk;
	}
}