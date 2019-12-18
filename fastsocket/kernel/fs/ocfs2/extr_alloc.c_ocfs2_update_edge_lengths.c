#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ocfs2_path {int p_tree_depth; TYPE_1__* p_node; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; } ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_cpos; int /*<<< orphan*/  e_int_clusters; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; int /*<<< orphan*/  l_next_free_rec; } ;
struct ocfs2_extent_block {unsigned long long h_next_leaf_blk; struct ocfs2_extent_list h_list; } ;
struct TYPE_9__ {scalar_t__ h_buffer_credits; } ;
typedef  TYPE_2__ handle_t ;
struct TYPE_10__ {scalar_t__ b_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  bh; struct ocfs2_extent_list* el; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_extend_trans (TYPE_2__*,scalar_t__) ; 
 int ocfs2_journal_access_path (int /*<<< orphan*/ ,TYPE_2__*,struct ocfs2_path*) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_rec_clusters (struct ocfs2_extent_list*,struct ocfs2_extent_rec*) ; 
 TYPE_3__* path_leaf_bh (struct ocfs2_path*) ; 

__attribute__((used)) static int ocfs2_update_edge_lengths(handle_t *handle,
				     struct ocfs2_extent_tree *et,
				     int subtree_index, struct ocfs2_path *path)
{
	int i, idx, ret;
	struct ocfs2_extent_rec *rec;
	struct ocfs2_extent_list *el;
	struct ocfs2_extent_block *eb;
	u32 range;

	/*
	 * In normal tree rotation process, we will never touch the
	 * tree branch above subtree_index and ocfs2_extend_rotate_transaction
	 * doesn't reserve the credits for them either.
	 *
	 * But we do have a special case here which will update the rightmost
	 * records for all the bh in the path.
	 * So we have to allocate extra credits and access them.
	 */
	ret = ocfs2_extend_trans(handle,
				 handle->h_buffer_credits + subtree_index);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_journal_access_path(et->et_ci, handle, path);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	/* Path should always be rightmost. */
	eb = (struct ocfs2_extent_block *)path_leaf_bh(path)->b_data;
	BUG_ON(eb->h_next_leaf_blk != 0ULL);

	el = &eb->h_list;
	BUG_ON(le16_to_cpu(el->l_next_free_rec) == 0);
	idx = le16_to_cpu(el->l_next_free_rec) - 1;
	rec = &el->l_recs[idx];
	range = le32_to_cpu(rec->e_cpos) + ocfs2_rec_clusters(el, rec);

	for (i = 0; i < path->p_tree_depth; i++) {
		el = path->p_node[i].el;
		idx = le16_to_cpu(el->l_next_free_rec) - 1;
		rec = &el->l_recs[idx];

		rec->e_int_clusters = cpu_to_le32(range);
		le32_add_cpu(&rec->e_int_clusters, -le32_to_cpu(rec->e_cpos));

		ocfs2_journal_dirty(handle, path->p_node[i].bh);
	}
out:
	return ret;
}