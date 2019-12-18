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
struct reiserfs_bitmap_info {scalar_t__ free_count; } ;
struct buffer_head {scalar_t__ b_data; int /*<<< orphan*/  b_blocknr; scalar_t__ b_size; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int /*<<< orphan*/  reiserfs_error (struct super_block*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_test_le_bit (int,unsigned long*) ; 

void reiserfs_cache_bitmap_metadata(struct super_block *sb,
                                    struct buffer_head *bh,
                                    struct reiserfs_bitmap_info *info)
{
	unsigned long *cur = (unsigned long *)(bh->b_data + bh->b_size);

	/* The first bit must ALWAYS be 1 */
	if (!reiserfs_test_le_bit(0, (unsigned long *)bh->b_data))
		reiserfs_error(sb, "reiserfs-2025", "bitmap block %lu is "
			       "corrupted: first bit must be 1", bh->b_blocknr);

	info->free_count = 0;

	while (--cur >= (unsigned long *)bh->b_data) {
		int i;

		/* 0 and ~0 are special, we can optimize for them */
		if (*cur == 0)
			info->free_count += BITS_PER_LONG;
		else if (*cur != ~0L)	/* A mix, investigate */
			for (i = BITS_PER_LONG - 1; i >= 0; i--)
				if (!reiserfs_test_le_bit(i, cur))
					info->free_count++;
	}
}