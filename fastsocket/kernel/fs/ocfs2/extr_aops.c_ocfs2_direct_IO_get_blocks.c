#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
struct inode {unsigned long i_blkbits; TYPE_1__* i_sb; } ;
struct buffer_head {unsigned long b_size; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_3__ {unsigned char s_blocksize_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (unsigned int) ; 
 int EIO ; 
 int /*<<< orphan*/  ML_ERROR ; 
 unsigned int OCFS2_EXT_REFCOUNTED ; 
 unsigned int OCFS2_EXT_UNWRITTEN ; 
 int /*<<< orphan*/  clear_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 unsigned long ocfs2_blocks_for_bytes (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int ocfs2_extent_map_get_blocks (struct inode*,scalar_t__,unsigned long*,unsigned long*,unsigned int*) ; 

__attribute__((used)) static int ocfs2_direct_IO_get_blocks(struct inode *inode, sector_t iblock,
				     struct buffer_head *bh_result, int create)
{
	int ret;
	u64 p_blkno, inode_blocks, contig_blocks;
	unsigned int ext_flags;
	unsigned char blocksize_bits = inode->i_sb->s_blocksize_bits;
	unsigned long max_blocks = bh_result->b_size >> inode->i_blkbits;

	/* This function won't even be called if the request isn't all
	 * nicely aligned and of the right size, so there's no need
	 * for us to check any of that. */

	inode_blocks = ocfs2_blocks_for_bytes(inode->i_sb, i_size_read(inode));

	/* This figures out the size of the next contiguous block, and
	 * our logical offset */
	ret = ocfs2_extent_map_get_blocks(inode, iblock, &p_blkno,
					  &contig_blocks, &ext_flags);
	if (ret) {
		mlog(ML_ERROR, "get_blocks() failed iblock=%llu\n",
		     (unsigned long long)iblock);
		ret = -EIO;
		goto bail;
	}

	/* We should already CoW the refcounted extent. */
	BUG_ON(ext_flags & OCFS2_EXT_REFCOUNTED);
	/*
	 * get_more_blocks() expects us to describe a hole by clearing
	 * the mapped bit on bh_result().
	 *
	 * Consider an unwritten extent as a hole.
	 */
	if (p_blkno && !(ext_flags & OCFS2_EXT_UNWRITTEN))
		map_bh(bh_result, inode->i_sb, p_blkno);
	else
		clear_buffer_mapped(bh_result);

	/* make sure we don't map more than max_blocks blocks here as
	   that's all the kernel will handle at this point. */
	if (max_blocks < contig_blocks)
		contig_blocks = max_blocks;
	bh_result->b_size = contig_blocks << blocksize_bits;
bail:
	return ret;
}