#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_path {scalar_t__ p_tree_depth; } ;
struct ocfs2_insert_type {scalar_t__ ins_split; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; } ;
struct ocfs2_extent_rec {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_7__ {int h_buffer_credits; } ;
typedef  TYPE_1__ handle_t ;

/* Variables and functions */
 scalar_t__ SPLIT_NONE ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_complete_edge_insert (TYPE_1__*,struct ocfs2_path*,struct ocfs2_path*,int) ; 
 int ocfs2_extend_trans (TYPE_1__*,int) ; 
 int ocfs2_find_subtree_root (struct ocfs2_extent_tree*,struct ocfs2_path*,struct ocfs2_path*) ; 
 int /*<<< orphan*/  ocfs2_insert_at_leaf (struct ocfs2_extent_tree*,struct ocfs2_extent_rec*,int /*<<< orphan*/ ,struct ocfs2_insert_type*) ; 
 int ocfs2_journal_access_path (int /*<<< orphan*/ ,TYPE_1__*,struct ocfs2_path*) ; 
 int ocfs2_journal_dirty (TYPE_1__*,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_split_record (struct ocfs2_extent_tree*,struct ocfs2_path*,struct ocfs2_path*,struct ocfs2_extent_rec*,scalar_t__) ; 
 struct buffer_head* path_leaf_bh (struct ocfs2_path*) ; 
 int /*<<< orphan*/  path_leaf_el (struct ocfs2_path*) ; 

__attribute__((used)) static int ocfs2_insert_path(handle_t *handle,
			     struct ocfs2_extent_tree *et,
			     struct ocfs2_path *left_path,
			     struct ocfs2_path *right_path,
			     struct ocfs2_extent_rec *insert_rec,
			     struct ocfs2_insert_type *insert)
{
	int ret, subtree_index;
	struct buffer_head *leaf_bh = path_leaf_bh(right_path);

	if (left_path) {
		int credits = handle->h_buffer_credits;

		/*
		 * There's a chance that left_path got passed back to
		 * us without being accounted for in the
		 * journal. Extend our transaction here to be sure we
		 * can change those blocks.
		 */
		credits += left_path->p_tree_depth;

		ret = ocfs2_extend_trans(handle, credits);
		if (ret < 0) {
			mlog_errno(ret);
			goto out;
		}

		ret = ocfs2_journal_access_path(et->et_ci, handle, left_path);
		if (ret < 0) {
			mlog_errno(ret);
			goto out;
		}
	}

	/*
	 * Pass both paths to the journal. The majority of inserts
	 * will be touching all components anyway.
	 */
	ret = ocfs2_journal_access_path(et->et_ci, handle, right_path);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}

	if (insert->ins_split != SPLIT_NONE) {
		/*
		 * We could call ocfs2_insert_at_leaf() for some types
		 * of splits, but it's easier to just let one separate
		 * function sort it all out.
		 */
		ocfs2_split_record(et, left_path, right_path,
				   insert_rec, insert->ins_split);

		/*
		 * Split might have modified either leaf and we don't
		 * have a guarantee that the later edge insert will
		 * dirty this for us.
		 */
		if (left_path)
			ret = ocfs2_journal_dirty(handle,
						  path_leaf_bh(left_path));
			if (ret)
				mlog_errno(ret);
	} else
		ocfs2_insert_at_leaf(et, insert_rec, path_leaf_el(right_path),
				     insert);

	ret = ocfs2_journal_dirty(handle, leaf_bh);
	if (ret)
		mlog_errno(ret);

	if (left_path) {
		/*
		 * The rotate code has indicated that we need to fix
		 * up portions of the tree after the insert.
		 *
		 * XXX: Should we extend the transaction here?
		 */
		subtree_index = ocfs2_find_subtree_root(et, left_path,
							right_path);
		ocfs2_complete_edge_insert(handle, left_path, right_path,
					   subtree_index);
	}

	ret = 0;
out:
	return ret;
}