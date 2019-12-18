#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_bits; int /*<<< orphan*/  bg_free_bits_count; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_total; int /*<<< orphan*/  i_used; } ;
struct TYPE_9__ {TYPE_3__ bitmap1; } ;
struct ocfs2_chain_list {int /*<<< orphan*/  cl_cpg; int /*<<< orphan*/  cl_next_free_rec; int /*<<< orphan*/  cl_count; TYPE_2__* cl_recs; } ;
struct TYPE_6__ {struct ocfs2_chain_list i_chain; } ;
struct ocfs2_dinode {void* i_size; int /*<<< orphan*/  i_clusters; TYPE_4__ id1; TYPE_1__ id2; } ;
struct ocfs2_alloc_context {scalar_t__ ac_last_group; } ;
struct inode {int /*<<< orphan*/  i_blocks; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_10__ {int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  ip_clusters; } ;
struct TYPE_7__ {void* c_blkno; int /*<<< orphan*/  c_total; int /*<<< orphan*/  c_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENOSPC ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 TYPE_5__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (void*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_block_group_fill (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,scalar_t__,size_t,struct ocfs2_chain_list*) ; 
 int ocfs2_calc_group_alloc_credits (int /*<<< orphan*/ ,scalar_t__) ; 
 int ocfs2_claim_clusters (struct ocfs2_super*,int /*<<< orphan*/ *,struct ocfs2_alloc_context*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_clusters_to_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 size_t ocfs2_find_smallest_chain (struct ocfs2_chain_list*) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_inode_sector_count (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_is_cluster_bitmap (struct inode*) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_reserve_clusters_with_limit (struct ocfs2_super*,scalar_t__,scalar_t__,int,struct ocfs2_alloc_context**) ; 
 int /*<<< orphan*/  ocfs2_set_new_buffer_uptodate (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int) ; 
 struct buffer_head* sb_getblk (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_block_group_alloc(struct ocfs2_super *osb,
				   struct inode *alloc_inode,
				   struct buffer_head *bh,
				   u64 max_block,
				   u64 *last_alloc_group,
				   int flags)
{
	int status, credits;
	struct ocfs2_dinode *fe = (struct ocfs2_dinode *) bh->b_data;
	struct ocfs2_chain_list *cl;
	struct ocfs2_alloc_context *ac = NULL;
	handle_t *handle = NULL;
	u32 bit_off, num_bits;
	u16 alloc_rec;
	u64 bg_blkno;
	struct buffer_head *bg_bh = NULL;
	struct ocfs2_group_desc *bg;

	BUG_ON(ocfs2_is_cluster_bitmap(alloc_inode));

	mlog_entry_void();

	cl = &fe->id2.i_chain;
	status = ocfs2_reserve_clusters_with_limit(osb,
						   le16_to_cpu(cl->cl_cpg),
						   max_block, flags, &ac);
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto bail;
	}

	credits = ocfs2_calc_group_alloc_credits(osb->sb,
						 le16_to_cpu(cl->cl_cpg));
	handle = ocfs2_start_trans(osb, credits);
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		handle = NULL;
		mlog_errno(status);
		goto bail;
	}

	if (last_alloc_group && *last_alloc_group != 0) {
		mlog(0, "use old allocation group %llu for block group alloc\n",
		     (unsigned long long)*last_alloc_group);
		ac->ac_last_group = *last_alloc_group;
	}
	status = ocfs2_claim_clusters(osb,
				      handle,
				      ac,
				      le16_to_cpu(cl->cl_cpg),
				      &bit_off,
				      &num_bits);
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto bail;
	}

	alloc_rec = ocfs2_find_smallest_chain(cl);

	/* setup the group */
	bg_blkno = ocfs2_clusters_to_blocks(osb->sb, bit_off);
	mlog(0, "new descriptor, record %u, at block %llu\n",
	     alloc_rec, (unsigned long long)bg_blkno);

	bg_bh = sb_getblk(osb->sb, bg_blkno);
	if (!bg_bh) {
		status = -EIO;
		mlog_errno(status);
		goto bail;
	}
	ocfs2_set_new_buffer_uptodate(INODE_CACHE(alloc_inode), bg_bh);

	status = ocfs2_block_group_fill(handle,
					alloc_inode,
					bg_bh,
					bg_blkno,
					alloc_rec,
					cl);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	bg = (struct ocfs2_group_desc *) bg_bh->b_data;

	status = ocfs2_journal_access_di(handle, INODE_CACHE(alloc_inode),
					 bh, OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	le32_add_cpu(&cl->cl_recs[alloc_rec].c_free,
		     le16_to_cpu(bg->bg_free_bits_count));
	le32_add_cpu(&cl->cl_recs[alloc_rec].c_total, le16_to_cpu(bg->bg_bits));
	cl->cl_recs[alloc_rec].c_blkno  = cpu_to_le64(bg_blkno);
	if (le16_to_cpu(cl->cl_next_free_rec) < le16_to_cpu(cl->cl_count))
		le16_add_cpu(&cl->cl_next_free_rec, 1);

	le32_add_cpu(&fe->id1.bitmap1.i_used, le16_to_cpu(bg->bg_bits) -
					le16_to_cpu(bg->bg_free_bits_count));
	le32_add_cpu(&fe->id1.bitmap1.i_total, le16_to_cpu(bg->bg_bits));
	le32_add_cpu(&fe->i_clusters, le16_to_cpu(cl->cl_cpg));

	status = ocfs2_journal_dirty(handle, bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	spin_lock(&OCFS2_I(alloc_inode)->ip_lock);
	OCFS2_I(alloc_inode)->ip_clusters = le32_to_cpu(fe->i_clusters);
	fe->i_size = cpu_to_le64(ocfs2_clusters_to_bytes(alloc_inode->i_sb,
					     le32_to_cpu(fe->i_clusters)));
	spin_unlock(&OCFS2_I(alloc_inode)->ip_lock);
	i_size_write(alloc_inode, le64_to_cpu(fe->i_size));
	alloc_inode->i_blocks = ocfs2_inode_sector_count(alloc_inode);

	status = 0;

	/* save the new last alloc group so that the caller can cache it. */
	if (last_alloc_group)
		*last_alloc_group = ac->ac_last_group;

bail:
	if (handle)
		ocfs2_commit_trans(osb, handle);

	if (ac)
		ocfs2_free_alloc_context(ac);

	brelse(bg_bh);

	mlog_exit(status);
	return status;
}