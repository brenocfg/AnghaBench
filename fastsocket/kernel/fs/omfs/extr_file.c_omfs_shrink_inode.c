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
struct omfs_sb_info {int s_mirrors; } ;
struct omfs_header {int dummy; } ;
struct omfs_extent_entry {int /*<<< orphan*/  e_blocks; int /*<<< orphan*/  e_cluster; } ;
struct omfs_extent {struct omfs_extent_entry e_entry; int /*<<< orphan*/  e_next; int /*<<< orphan*/  e_extent_count; } ;
struct inode {scalar_t__ i_ino; scalar_t__ i_size; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {char* b_data; } ;

/* Variables and functions */
 int EIO ; 
 size_t OMFS_EXTENT_CONT ; 
 size_t OMFS_EXTENT_START ; 
 struct omfs_sb_info* OMFS_SB (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clus_to_blk (struct omfs_sb_info*,scalar_t__) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  omfs_clear_range (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ omfs_is_bad (struct omfs_sb_info*,struct omfs_header*,scalar_t__) ; 
 int /*<<< orphan*/  omfs_make_empty_table (struct buffer_head*,int) ; 
 int omfs_max_extents (struct omfs_sb_info*,size_t) ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int omfs_shrink_inode(struct inode *inode)
{
	struct omfs_sb_info *sbi = OMFS_SB(inode->i_sb);
	struct omfs_extent *oe;
	struct omfs_extent_entry *entry;
	struct buffer_head *bh;
	u64 next, last;
	u32 extent_count;
	u32 max_extents;
	int ret;

	/* traverse extent table, freeing each entry that is greater
	 * than inode->i_size;
	 */
	next = inode->i_ino;

	/* only support truncate -> 0 for now */
	ret = -EIO;
	if (inode->i_size != 0)
		goto out;

	bh = sb_bread(inode->i_sb, clus_to_blk(sbi, next));
	if (!bh)
		goto out;

	oe = (struct omfs_extent *)(&bh->b_data[OMFS_EXTENT_START]);
	max_extents = omfs_max_extents(sbi, OMFS_EXTENT_START);

	for (;;) {

		if (omfs_is_bad(sbi, (struct omfs_header *) bh->b_data, next))
			goto out_brelse;

		extent_count = be32_to_cpu(oe->e_extent_count);

		if (extent_count > max_extents)
			goto out_brelse;

		last = next;
		next = be64_to_cpu(oe->e_next);
		entry = &oe->e_entry;

		/* ignore last entry as it is the terminator */
		for (; extent_count > 1; extent_count--) {
			u64 start, count;
			start = be64_to_cpu(entry->e_cluster);
			count = be64_to_cpu(entry->e_blocks);

			omfs_clear_range(inode->i_sb, start, (int) count);
			entry++;
		}
		omfs_make_empty_table(bh, (char *) oe - bh->b_data);
		mark_buffer_dirty(bh);
		brelse(bh);

		if (last != inode->i_ino)
			omfs_clear_range(inode->i_sb, last, sbi->s_mirrors);

		if (next == ~0)
			break;

		bh = sb_bread(inode->i_sb, clus_to_blk(sbi, next));
		if (!bh)
			goto out;
		oe = (struct omfs_extent *) (&bh->b_data[OMFS_EXTENT_CONT]);
		max_extents = omfs_max_extents(sbi, OMFS_EXTENT_CONT);
	}
	ret = 0;
out:
	return ret;
out_brelse:
	brelse(bh);
	return ret;
}