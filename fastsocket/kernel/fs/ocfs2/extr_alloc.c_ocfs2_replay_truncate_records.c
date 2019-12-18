#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ocfs2_truncate_rec {int /*<<< orphan*/  t_start; int /*<<< orphan*/  t_clusters; } ;
struct ocfs2_truncate_log {struct ocfs2_truncate_rec* tl_recs; int /*<<< orphan*/  tl_used; } ;
struct ocfs2_super {struct buffer_head* osb_tl_bh; struct inode* osb_tl_inode; } ;
struct TYPE_2__ {struct ocfs2_truncate_log i_dealloc; } ;
struct ocfs2_dinode {TYPE_1__ id2; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  OCFS2_TRUNCATE_LOG_FLUSH_ONE_REC ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 scalar_t__ ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,unsigned int) ; 
 int ocfs2_extend_trans (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ocfs2_free_clusters (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,scalar_t__,unsigned int) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 

__attribute__((used)) static int ocfs2_replay_truncate_records(struct ocfs2_super *osb,
					 handle_t *handle,
					 struct inode *data_alloc_inode,
					 struct buffer_head *data_alloc_bh)
{
	int status = 0;
	int i;
	unsigned int num_clusters;
	u64 start_blk;
	struct ocfs2_truncate_rec rec;
	struct ocfs2_dinode *di;
	struct ocfs2_truncate_log *tl;
	struct inode *tl_inode = osb->osb_tl_inode;
	struct buffer_head *tl_bh = osb->osb_tl_bh;

	mlog_entry_void();

	di = (struct ocfs2_dinode *) tl_bh->b_data;
	tl = &di->id2.i_dealloc;
	i = le16_to_cpu(tl->tl_used) - 1;
	while (i >= 0) {
		/* Caller has given us at least enough credits to
		 * update the truncate log dinode */
		status = ocfs2_journal_access_di(handle, INODE_CACHE(tl_inode), tl_bh,
						 OCFS2_JOURNAL_ACCESS_WRITE);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}

		tl->tl_used = cpu_to_le16(i);

		status = ocfs2_journal_dirty(handle, tl_bh);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}

		/* TODO: Perhaps we can calculate the bulk of the
		 * credits up front rather than extending like
		 * this. */
		status = ocfs2_extend_trans(handle,
					    OCFS2_TRUNCATE_LOG_FLUSH_ONE_REC);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}

		rec = tl->tl_recs[i];
		start_blk = ocfs2_clusters_to_blocks(data_alloc_inode->i_sb,
						    le32_to_cpu(rec.t_start));
		num_clusters = le32_to_cpu(rec.t_clusters);

		/* if start_blk is not set, we ignore the record as
		 * invalid. */
		if (start_blk) {
			mlog(0, "free record %d, start = %u, clusters = %u\n",
			     i, le32_to_cpu(rec.t_start), num_clusters);

			status = ocfs2_free_clusters(handle, data_alloc_inode,
						     data_alloc_bh, start_blk,
						     num_clusters);
			if (status < 0) {
				mlog_errno(status);
				goto bail;
			}
		}
		i--;
	}

bail:
	mlog_exit(status);
	return status;
}