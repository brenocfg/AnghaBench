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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct omfs_sb_info {int dummy; } ;
struct omfs_header {int dummy; } ;
struct omfs_extent_entry {int dummy; } ;
struct omfs_extent {struct omfs_extent_entry e_entry; int /*<<< orphan*/  e_next; int /*<<< orphan*/  e_extent_count; } ;
struct inode {int i_blkbits; scalar_t__ i_ino; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int b_size; int /*<<< orphan*/ * b_data; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int EIO ; 
 size_t OMFS_EXTENT_CONT ; 
 size_t OMFS_EXTENT_START ; 
 struct omfs_sb_info* OMFS_SB (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ clus_to_blk (struct omfs_sb_info*,scalar_t__) ; 
 scalar_t__ find_block (struct inode*,struct omfs_extent_entry*,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int omfs_grow_extent (struct inode*,struct omfs_extent*,scalar_t__*) ; 
 scalar_t__ omfs_is_bad (struct omfs_sb_info*,struct omfs_header*,scalar_t__) ; 
 int omfs_max_extents (struct omfs_sb_info*,size_t) ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int omfs_get_block(struct inode *inode, sector_t block,
			  struct buffer_head *bh_result, int create)
{
	struct buffer_head *bh;
	sector_t next, offset;
	int ret;
	u64 new_block;
	u32 max_extents;
	int extent_count;
	struct omfs_extent *oe;
	struct omfs_extent_entry *entry;
	struct omfs_sb_info *sbi = OMFS_SB(inode->i_sb);
	int max_blocks = bh_result->b_size >> inode->i_blkbits;
	int remain;

	ret = -EIO;
	bh = sb_bread(inode->i_sb, clus_to_blk(sbi, inode->i_ino));
	if (!bh)
		goto out;

	oe = (struct omfs_extent *)(&bh->b_data[OMFS_EXTENT_START]);
	max_extents = omfs_max_extents(sbi, OMFS_EXTENT_START);
	next = inode->i_ino;

	for (;;) {

		if (omfs_is_bad(sbi, (struct omfs_header *) bh->b_data, next))
			goto out_brelse;

		extent_count = be32_to_cpu(oe->e_extent_count);
		next = be64_to_cpu(oe->e_next);
		entry = &oe->e_entry;

		if (extent_count > max_extents)
			goto out_brelse;

		offset = find_block(inode, entry, block, extent_count, &remain);
		if (offset > 0) {
			ret = 0;
			map_bh(bh_result, inode->i_sb, offset);
			if (remain > max_blocks)
				remain = max_blocks;
			bh_result->b_size = (remain << inode->i_blkbits);
			goto out_brelse;
		}
		if (next == ~0)
			break;

		brelse(bh);
		bh = sb_bread(inode->i_sb, clus_to_blk(sbi, next));
		if (!bh)
			goto out;
		oe = (struct omfs_extent *) (&bh->b_data[OMFS_EXTENT_CONT]);
		max_extents = omfs_max_extents(sbi, OMFS_EXTENT_CONT);
	}
	if (create) {
		ret = omfs_grow_extent(inode, oe, &new_block);
		if (ret == 0) {
			mark_buffer_dirty(bh);
			mark_inode_dirty(inode);
			map_bh(bh_result, inode->i_sb,
					clus_to_blk(sbi, new_block));
		}
	}
out_brelse:
	brelse(bh);
out:
	return ret;
}