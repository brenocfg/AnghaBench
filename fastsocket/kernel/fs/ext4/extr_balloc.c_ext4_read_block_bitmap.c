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
struct ext4_group_desc {int bg_flags; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  ext4_group_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_BG_BLOCK_UNINIT ; 
 scalar_t__ bh_submit_read (struct buffer_head*) ; 
 scalar_t__ bitmap_uptodate (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_block_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_error (struct super_block*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_init_block_bitmap (struct super_block*,struct buffer_head*,int /*<<< orphan*/ ,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_lock_group (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_unlock_group (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_valid_block_bitmap (struct super_block*,struct ext4_group_desc*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 struct buffer_head* sb_getblk (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bitmap_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

struct buffer_head *
ext4_read_block_bitmap(struct super_block *sb, ext4_group_t block_group)
{
	struct ext4_group_desc *desc;
	struct buffer_head *bh = NULL;
	ext4_fsblk_t bitmap_blk;

	desc = ext4_get_group_desc(sb, block_group, NULL);
	if (!desc)
		return NULL;
	bitmap_blk = ext4_block_bitmap(sb, desc);
	bh = sb_getblk(sb, bitmap_blk);
	if (unlikely(!bh)) {
		ext4_error(sb, "Cannot read block bitmap - "
			    "block_group = %u, block_bitmap = %llu",
			    block_group, bitmap_blk);
		return NULL;
	}

	if (bitmap_uptodate(bh))
		return bh;

	lock_buffer(bh);
	if (bitmap_uptodate(bh)) {
		unlock_buffer(bh);
		return bh;
	}
	ext4_lock_group(sb, block_group);
	if (desc->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT)) {
		ext4_init_block_bitmap(sb, bh, block_group, desc);
		set_bitmap_uptodate(bh);
		set_buffer_uptodate(bh);
		ext4_unlock_group(sb, block_group);
		unlock_buffer(bh);
		return bh;
	}
	ext4_unlock_group(sb, block_group);
	if (buffer_uptodate(bh)) {
		/*
		 * if not uninit if bh is uptodate,
		 * bitmap is also uptodate
		 */
		set_bitmap_uptodate(bh);
		unlock_buffer(bh);
		return bh;
	}
	/*
	 * submit the buffer_head for read. We can
	 * safely mark the bitmap as uptodate now.
	 * We do it here so the bitmap uptodate bit
	 * get set with buffer lock held.
	 */
	set_bitmap_uptodate(bh);
	if (bh_submit_read(bh) < 0) {
		put_bh(bh);
		ext4_error(sb, "Cannot read block bitmap - "
			    "block_group = %u, block_bitmap = %llu",
			    block_group, bitmap_blk);
		return NULL;
	}
	ext4_valid_block_bitmap(sb, desc, block_group, bh);
	/*
	 * file system mounted not to panic on error,
	 * continue with corrupt bitmap
	 */
	return bh;
}