#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ocfs2_refcount_rec {int /*<<< orphan*/  r_cpos; } ;
struct ocfs2_refcount_block {void* rf_cpos; void* rf_flags; } ;
struct ocfs2_path {int dummy; } ;
struct ocfs2_extent_tree {int dummy; } ;
struct ocfs2_extent_list {TYPE_1__* l_recs; int /*<<< orphan*/  l_next_free_rec; } ;
struct ocfs2_caching_info {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_9__ {scalar_t__ h_buffer_credits; } ;
typedef  TYPE_2__ handle_t ;
struct TYPE_8__ {void* e_cpos; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int OCFS2_32BIT_POS_MASK ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int OCFS2_REFCOUNT_TREE_FL ; 
 void* cpu_to_le32 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (void*) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_extend_trans (TYPE_2__*,scalar_t__) ; 
 int ocfs2_find_path (struct ocfs2_caching_info*,struct ocfs2_path*,int) ; 
 int /*<<< orphan*/  ocfs2_free_path (struct ocfs2_path*) ; 
 int /*<<< orphan*/  ocfs2_init_refcount_extent_tree (struct ocfs2_extent_tree*,struct ocfs2_caching_info*,struct buffer_head*) ; 
 int ocfs2_journal_access_eb (TYPE_2__*,struct ocfs2_caching_info*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_rb (TYPE_2__*,struct ocfs2_caching_info*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (TYPE_2__*,struct buffer_head*) ; 
 struct ocfs2_path* ocfs2_new_path_from_et (struct ocfs2_extent_tree*) ; 
 struct buffer_head* path_leaf_bh (struct ocfs2_path*) ; 
 struct ocfs2_extent_list* path_leaf_el (struct ocfs2_path*) ; 

__attribute__((used)) static int ocfs2_adjust_refcount_rec(handle_t *handle,
				     struct ocfs2_caching_info *ci,
				     struct buffer_head *ref_root_bh,
				     struct buffer_head *ref_leaf_bh,
				     struct ocfs2_refcount_rec *rec)
{
	int ret = 0, i;
	u32 new_cpos, old_cpos;
	struct ocfs2_path *path = NULL;
	struct ocfs2_extent_tree et;
	struct ocfs2_refcount_block *rb =
		(struct ocfs2_refcount_block *)ref_root_bh->b_data;
	struct ocfs2_extent_list *el;

	if (!(le32_to_cpu(rb->rf_flags) & OCFS2_REFCOUNT_TREE_FL))
		goto out;

	rb = (struct ocfs2_refcount_block *)ref_leaf_bh->b_data;
	old_cpos = le32_to_cpu(rb->rf_cpos);
	new_cpos = le64_to_cpu(rec->r_cpos) & OCFS2_32BIT_POS_MASK;
	if (old_cpos <= new_cpos)
		goto out;

	ocfs2_init_refcount_extent_tree(&et, ci, ref_root_bh);

	path = ocfs2_new_path_from_et(&et);
	if (!path) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_find_path(ci, path, old_cpos);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	/*
	 * 2 more credits, one for the leaf refcount block, one for
	 * the extent block contains the extent rec.
	 */
	ret = ocfs2_extend_trans(handle, handle->h_buffer_credits + 2);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_journal_access_rb(handle, ci, ref_leaf_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_journal_access_eb(handle, ci, path_leaf_bh(path),
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}

	/* change the leaf extent block first. */
	el = path_leaf_el(path);

	for (i = 0; i < le16_to_cpu(el->l_next_free_rec); i++)
		if (le32_to_cpu(el->l_recs[i].e_cpos) == old_cpos)
			break;

	BUG_ON(i == le16_to_cpu(el->l_next_free_rec));

	el->l_recs[i].e_cpos = cpu_to_le32(new_cpos);

	/* change the r_cpos in the leaf block. */
	rb->rf_cpos = cpu_to_le32(new_cpos);

	ocfs2_journal_dirty(handle, path_leaf_bh(path));
	ocfs2_journal_dirty(handle, ref_leaf_bh);

out:
	ocfs2_free_path(path);
	return ret;
}