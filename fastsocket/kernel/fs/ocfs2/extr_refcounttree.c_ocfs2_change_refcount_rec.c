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
struct ocfs2_refcount_rec {int /*<<< orphan*/  r_refcount; } ;
struct ocfs2_refcount_list {int /*<<< orphan*/  rl_used; struct ocfs2_refcount_rec* rl_recs; } ;
struct ocfs2_refcount_block {struct ocfs2_refcount_list rf_records; } ;
struct ocfs2_caching_info {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct ocfs2_refcount_rec*,struct ocfs2_refcount_rec*,int) ; 
 int /*<<< orphan*/  memset (struct ocfs2_refcount_rec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_journal_access_rb (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_refcount_rec_merge (struct ocfs2_refcount_block*,int) ; 

__attribute__((used)) static int ocfs2_change_refcount_rec(handle_t *handle,
				     struct ocfs2_caching_info *ci,
				     struct buffer_head *ref_leaf_bh,
				     int index, int merge, int change)
{
	int ret;
	struct ocfs2_refcount_block *rb =
			(struct ocfs2_refcount_block *)ref_leaf_bh->b_data;
	struct ocfs2_refcount_list *rl = &rb->rf_records;
	struct ocfs2_refcount_rec *rec = &rl->rl_recs[index];

	ret = ocfs2_journal_access_rb(handle, ci, ref_leaf_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	mlog(0, "change index %d, old count %u, change %d\n", index,
	     le32_to_cpu(rec->r_refcount), change);
	le32_add_cpu(&rec->r_refcount, change);

	if (!rec->r_refcount) {
		if (index != le16_to_cpu(rl->rl_used) - 1) {
			memmove(rec, rec + 1,
				(le16_to_cpu(rl->rl_used) - index - 1) *
				sizeof(struct ocfs2_refcount_rec));
			memset(&rl->rl_recs[le16_to_cpu(rl->rl_used) - 1],
			       0, sizeof(struct ocfs2_refcount_rec));
		}

		le16_add_cpu(&rl->rl_used, -1);
	} else if (merge)
		ocfs2_refcount_rec_merge(rb, index);

	ret = ocfs2_journal_dirty(handle, ref_leaf_bh);
	if (ret)
		mlog_errno(ret);
out:
	return ret;
}