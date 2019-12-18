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
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int s_blocksize; } ;
struct reiserfs_bitmap_info {int free_count; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 struct reiserfs_bitmap_info* SB_AP_BITMAP (struct super_block*) ; 
 int UINT_MAX ; 
 int bmap_hash_id (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct buffer_head* reiserfs_read_bitmap_block (struct super_block*,int) ; 

__attribute__((used)) static inline int block_group_used(struct super_block *s, u32 id)
{
	int bm = bmap_hash_id(s, id);
	struct reiserfs_bitmap_info *info = &SB_AP_BITMAP(s)[bm];

	/* If we don't have cached information on this bitmap block, we're
	 * going to have to load it later anyway. Loading it here allows us
	 * to make a better decision. This favors long-term performance gain
	 * with a better on-disk layout vs. a short term gain of skipping the
	 * read and potentially having a bad placement. */
	if (info->free_count == UINT_MAX) {
		struct buffer_head *bh = reiserfs_read_bitmap_block(s, bm);
		brelse(bh);
	}

	if (info->free_count > ((s->s_blocksize << 3) * 60 / 100)) {
		return 0;
	}
	return 1;
}