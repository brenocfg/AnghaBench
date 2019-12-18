#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_free_bits_count; int /*<<< orphan*/  bg_blkno; int /*<<< orphan*/  bg_next_group; } ;
struct TYPE_10__ {int /*<<< orphan*/  i_used; } ;
struct TYPE_11__ {TYPE_2__ bitmap1; } ;
struct TYPE_9__ {int /*<<< orphan*/  i_chain; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_blkno; TYPE_3__ id1; TYPE_1__ id2; } ;
struct ocfs2_chain_list {TYPE_4__* cl_recs; } ;
struct ocfs2_alloc_context {size_t ac_chain; int (* ac_group_search ) (struct inode*,struct buffer_head*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,size_t*,size_t*) ;TYPE_5__* ac_bh; scalar_t__ ac_allow_chain_relink; int /*<<< orphan*/  ac_max_block; struct inode* ac_inode; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_14__ {scalar_t__ ip_blkno; } ;
struct TYPE_13__ {scalar_t__ b_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  c_free; int /*<<< orphan*/  c_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 TYPE_8__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned int,unsigned long long,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 scalar_t__ ocfs2_block_group_reasonably_empty (struct ocfs2_group_desc*,unsigned int) ; 
 int ocfs2_block_group_set_bits (int /*<<< orphan*/ *,struct inode*,struct ocfs2_group_desc*,struct buffer_head*,size_t,unsigned int) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int ocfs2_read_group_descriptor (struct inode*,struct ocfs2_dinode*,scalar_t__,struct buffer_head**) ; 
 int ocfs2_relink_block_group (int /*<<< orphan*/ *,struct inode*,TYPE_5__*,struct buffer_head*,struct buffer_head*,size_t) ; 
 int stub1 (struct inode*,struct buffer_head*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,size_t*,size_t*) ; 

__attribute__((used)) static int ocfs2_search_chain(struct ocfs2_alloc_context *ac,
			      handle_t *handle,
			      u32 bits_wanted,
			      u32 min_bits,
			      u16 *bit_off,
			      unsigned int *num_bits,
			      u64 *bg_blkno,
			      u16 *bits_left)
{
	int status;
	u16 chain, tmp_bits;
	u32 tmp_used;
	u64 next_group;
	struct inode *alloc_inode = ac->ac_inode;
	struct buffer_head *group_bh = NULL;
	struct buffer_head *prev_group_bh = NULL;
	struct ocfs2_dinode *fe = (struct ocfs2_dinode *) ac->ac_bh->b_data;
	struct ocfs2_chain_list *cl = (struct ocfs2_chain_list *) &fe->id2.i_chain;
	struct ocfs2_group_desc *bg;

	chain = ac->ac_chain;
	mlog(0, "trying to alloc %u bits from chain %u, inode %llu\n",
	     bits_wanted, chain,
	     (unsigned long long)OCFS2_I(alloc_inode)->ip_blkno);

	status = ocfs2_read_group_descriptor(alloc_inode, fe,
					     le64_to_cpu(cl->cl_recs[chain].c_blkno),
					     &group_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}
	bg = (struct ocfs2_group_desc *) group_bh->b_data;

	status = -ENOSPC;
	/* for now, the chain search is a bit simplistic. We just use
	 * the 1st group with any empty bits. */
	while ((status = ac->ac_group_search(alloc_inode, group_bh,
					     bits_wanted, min_bits,
					     ac->ac_max_block, bit_off,
					     &tmp_bits)) == -ENOSPC) {
		if (!bg->bg_next_group)
			break;

		brelse(prev_group_bh);
		prev_group_bh = NULL;

		next_group = le64_to_cpu(bg->bg_next_group);
		prev_group_bh = group_bh;
		group_bh = NULL;
		status = ocfs2_read_group_descriptor(alloc_inode, fe,
						     next_group, &group_bh);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}
		bg = (struct ocfs2_group_desc *) group_bh->b_data;
	}
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto bail;
	}

	mlog(0, "alloc succeeds: we give %u bits from block group %llu\n",
	     tmp_bits, (unsigned long long)le64_to_cpu(bg->bg_blkno));

	*num_bits = tmp_bits;

	BUG_ON(*num_bits == 0);

	/*
	 * Keep track of previous block descriptor read. When
	 * we find a target, if we have read more than X
	 * number of descriptors, and the target is reasonably
	 * empty, relink him to top of his chain.
	 *
	 * We've read 0 extra blocks and only send one more to
	 * the transaction, yet the next guy to search has a
	 * much easier time.
	 *
	 * Do this *after* figuring out how many bits we're taking out
	 * of our target group.
	 */
	if (ac->ac_allow_chain_relink &&
	    (prev_group_bh) &&
	    (ocfs2_block_group_reasonably_empty(bg, *num_bits))) {
		status = ocfs2_relink_block_group(handle, alloc_inode,
						  ac->ac_bh, group_bh,
						  prev_group_bh, chain);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}
	}

	/* Ok, claim our bits now: set the info on dinode, chainlist
	 * and then the group */
	status = ocfs2_journal_access_di(handle,
					 INODE_CACHE(alloc_inode),
					 ac->ac_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	tmp_used = le32_to_cpu(fe->id1.bitmap1.i_used);
	fe->id1.bitmap1.i_used = cpu_to_le32(*num_bits + tmp_used);
	le32_add_cpu(&cl->cl_recs[chain].c_free, -(*num_bits));

	status = ocfs2_journal_dirty(handle,
				     ac->ac_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = ocfs2_block_group_set_bits(handle,
					    alloc_inode,
					    bg,
					    group_bh,
					    *bit_off,
					    *num_bits);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	mlog(0, "Allocated %u bits from suballocator %llu\n", *num_bits,
	     (unsigned long long)le64_to_cpu(fe->i_blkno));

	*bg_blkno = le64_to_cpu(bg->bg_blkno);
	*bits_left = le16_to_cpu(bg->bg_free_bits_count);
bail:
	brelse(group_bh);
	brelse(prev_group_bh);

	mlog_exit(status);
	return status;
}