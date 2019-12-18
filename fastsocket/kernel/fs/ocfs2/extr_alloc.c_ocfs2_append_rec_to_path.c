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
typedef  scalar_t__ u32 ;
struct ocfs2_path {scalar_t__ p_tree_depth; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; } ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_cpos; } ;
struct ocfs2_extent_list {int /*<<< orphan*/ * l_recs; int /*<<< orphan*/  l_next_free_rec; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_adjust_rightmost_records (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct ocfs2_path*,struct ocfs2_extent_rec*) ; 
 int ocfs2_find_cpos_for_left_leaf (int /*<<< orphan*/ ,struct ocfs2_path*,scalar_t__*) ; 
 int ocfs2_find_path (int /*<<< orphan*/ ,struct ocfs2_path*,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_free_path (struct ocfs2_path*) ; 
 scalar_t__ ocfs2_is_empty_extent (int /*<<< orphan*/ *) ; 
 int ocfs2_journal_access_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ocfs2_path*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_get_super (int /*<<< orphan*/ ) ; 
 struct ocfs2_path* ocfs2_new_path_from_path (struct ocfs2_path*) ; 
 struct ocfs2_extent_list* path_leaf_el (struct ocfs2_path*) ; 

__attribute__((used)) static int ocfs2_append_rec_to_path(handle_t *handle,
				    struct ocfs2_extent_tree *et,
				    struct ocfs2_extent_rec *insert_rec,
				    struct ocfs2_path *right_path,
				    struct ocfs2_path **ret_left_path)
{
	int ret, next_free;
	struct ocfs2_extent_list *el;
	struct ocfs2_path *left_path = NULL;

	*ret_left_path = NULL;

	/*
	 * This shouldn't happen for non-trees. The extent rec cluster
	 * count manipulation below only works for interior nodes.
	 */
	BUG_ON(right_path->p_tree_depth == 0);

	/*
	 * If our appending insert is at the leftmost edge of a leaf,
	 * then we might need to update the rightmost records of the
	 * neighboring path.
	 */
	el = path_leaf_el(right_path);
	next_free = le16_to_cpu(el->l_next_free_rec);
	if (next_free == 0 ||
	    (next_free == 1 && ocfs2_is_empty_extent(&el->l_recs[0]))) {
		u32 left_cpos;

		ret = ocfs2_find_cpos_for_left_leaf(ocfs2_metadata_cache_get_super(et->et_ci),
						    right_path, &left_cpos);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		mlog(0, "Append may need a left path update. cpos: %u, "
		     "left_cpos: %u\n", le32_to_cpu(insert_rec->e_cpos),
		     left_cpos);

		/*
		 * No need to worry if the append is already in the
		 * leftmost leaf.
		 */
		if (left_cpos) {
			left_path = ocfs2_new_path_from_path(right_path);
			if (!left_path) {
				ret = -ENOMEM;
				mlog_errno(ret);
				goto out;
			}

			ret = ocfs2_find_path(et->et_ci, left_path,
					      left_cpos);
			if (ret) {
				mlog_errno(ret);
				goto out;
			}

			/*
			 * ocfs2_insert_path() will pass the left_path to the
			 * journal for us.
			 */
		}
	}

	ret = ocfs2_journal_access_path(et->et_ci, handle, right_path);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ocfs2_adjust_rightmost_records(handle, et, right_path, insert_rec);

	*ret_left_path = left_path;
	ret = 0;
out:
	if (ret != 0)
		ocfs2_free_path(left_path);

	return ret;
}