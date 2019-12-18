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
typedef  unsigned long long u16 ;
struct ocfs2_dinode {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_block_to_cluster_group (struct inode*,scalar_t__,scalar_t__*,unsigned long long*) ; 
 int /*<<< orphan*/  ocfs2_blocks_to_clusters (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_free_suballoc_bits (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,unsigned long long,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_local_alloc_seen_free_bits (int /*<<< orphan*/ ,unsigned int) ; 

int ocfs2_free_clusters(handle_t *handle,
		       struct inode *bitmap_inode,
		       struct buffer_head *bitmap_bh,
		       u64 start_blk,
		       unsigned int num_clusters)
{
	int status;
	u16 bg_start_bit;
	u64 bg_blkno;
	struct ocfs2_dinode *fe;

	/* You can't ever have a contiguous set of clusters
	 * bigger than a block group bitmap so we never have to worry
	 * about looping on them. */

	mlog_entry_void();

	/* This is expensive. We can safely remove once this stuff has
	 * gotten tested really well. */
	BUG_ON(start_blk != ocfs2_clusters_to_blocks(bitmap_inode->i_sb, ocfs2_blocks_to_clusters(bitmap_inode->i_sb, start_blk)));

	fe = (struct ocfs2_dinode *) bitmap_bh->b_data;

	ocfs2_block_to_cluster_group(bitmap_inode, start_blk, &bg_blkno,
				     &bg_start_bit);

	mlog(0, "want to free %u clusters starting at block %llu\n",
	     num_clusters, (unsigned long long)start_blk);
	mlog(0, "bg_blkno = %llu, bg_start_bit = %u\n",
	     (unsigned long long)bg_blkno, bg_start_bit);

	status = ocfs2_free_suballoc_bits(handle, bitmap_inode, bitmap_bh,
					  bg_start_bit, bg_blkno,
					  num_clusters);
	if (status < 0) {
		mlog_errno(status);
		goto out;
	}

	ocfs2_local_alloc_seen_free_bits(OCFS2_SB(bitmap_inode->i_sb),
					 num_clusters);

out:
	mlog_exit(status);
	return status;
}