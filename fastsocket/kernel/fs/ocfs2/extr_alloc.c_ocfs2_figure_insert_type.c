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
struct ocfs2_path {int dummy; } ;
struct ocfs2_insert_type {scalar_t__ ins_contig; scalar_t__ ins_contig_index; void* ins_tree_depth; int /*<<< orphan*/  ins_split; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; struct ocfs2_extent_list* et_root_el; } ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_cpos; } ;
struct ocfs2_extent_list {scalar_t__ l_next_free_rec; scalar_t__ l_count; scalar_t__ l_tree_depth; } ;
struct ocfs2_extent_block {struct ocfs2_extent_list h_list; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_2__ {scalar_t__ b_blocknr; } ;

/* Variables and functions */
 scalar_t__ CONTIG_LEFT ; 
 scalar_t__ CONTIG_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SPLIT_NONE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 scalar_t__ ocfs2_et_get_last_eb_blk (struct ocfs2_extent_tree*) ; 
 int /*<<< orphan*/  ocfs2_figure_appending_type (struct ocfs2_insert_type*,struct ocfs2_extent_list*,struct ocfs2_extent_rec*) ; 
 int /*<<< orphan*/  ocfs2_figure_contig_type (struct ocfs2_extent_tree*,struct ocfs2_insert_type*,struct ocfs2_extent_list*,struct ocfs2_extent_rec*) ; 
 int ocfs2_find_path (int /*<<< orphan*/ ,struct ocfs2_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_free_path (struct ocfs2_path*) ; 
 struct ocfs2_path* ocfs2_new_path_from_et (struct ocfs2_extent_tree*) ; 
 int ocfs2_read_extent_block (int /*<<< orphan*/ ,scalar_t__,struct buffer_head**) ; 
 TYPE_1__* path_leaf_bh (struct ocfs2_path*) ; 
 struct ocfs2_extent_list* path_leaf_el (struct ocfs2_path*) ; 

__attribute__((used)) static int ocfs2_figure_insert_type(struct ocfs2_extent_tree *et,
				    struct buffer_head **last_eb_bh,
				    struct ocfs2_extent_rec *insert_rec,
				    int *free_records,
				    struct ocfs2_insert_type *insert)
{
	int ret;
	struct ocfs2_extent_block *eb;
	struct ocfs2_extent_list *el;
	struct ocfs2_path *path = NULL;
	struct buffer_head *bh = NULL;

	insert->ins_split = SPLIT_NONE;

	el = et->et_root_el;
	insert->ins_tree_depth = le16_to_cpu(el->l_tree_depth);

	if (el->l_tree_depth) {
		/*
		 * If we have tree depth, we read in the
		 * rightmost extent block ahead of time as
		 * ocfs2_figure_insert_type() and ocfs2_add_branch()
		 * may want it later.
		 */
		ret = ocfs2_read_extent_block(et->et_ci,
					      ocfs2_et_get_last_eb_blk(et),
					      &bh);
		if (ret) {
			mlog_exit(ret);
			goto out;
		}
		eb = (struct ocfs2_extent_block *) bh->b_data;
		el = &eb->h_list;
	}

	/*
	 * Unless we have a contiguous insert, we'll need to know if
	 * there is room left in our allocation tree for another
	 * extent record.
	 *
	 * XXX: This test is simplistic, we can search for empty
	 * extent records too.
	 */
	*free_records = le16_to_cpu(el->l_count) -
		le16_to_cpu(el->l_next_free_rec);

	if (!insert->ins_tree_depth) {
		ocfs2_figure_contig_type(et, insert, el, insert_rec);
		ocfs2_figure_appending_type(insert, el, insert_rec);
		return 0;
	}

	path = ocfs2_new_path_from_et(et);
	if (!path) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	/*
	 * In the case that we're inserting past what the tree
	 * currently accounts for, ocfs2_find_path() will return for
	 * us the rightmost tree path. This is accounted for below in
	 * the appending code.
	 */
	ret = ocfs2_find_path(et->et_ci, path, le32_to_cpu(insert_rec->e_cpos));
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	el = path_leaf_el(path);

	/*
	 * Now that we have the path, there's two things we want to determine:
	 * 1) Contiguousness (also set contig_index if this is so)
	 *
	 * 2) Are we doing an append? We can trivially break this up
         *     into two types of appends: simple record append, or a
         *     rotate inside the tail leaf.
	 */
	ocfs2_figure_contig_type(et, insert, el, insert_rec);

	/*
	 * The insert code isn't quite ready to deal with all cases of
	 * left contiguousness. Specifically, if it's an insert into
	 * the 1st record in a leaf, it will require the adjustment of
	 * cluster count on the last record of the path directly to it's
	 * left. For now, just catch that case and fool the layers
	 * above us. This works just fine for tree_depth == 0, which
	 * is why we allow that above.
	 */
	if (insert->ins_contig == CONTIG_LEFT &&
	    insert->ins_contig_index == 0)
		insert->ins_contig = CONTIG_NONE;

	/*
	 * Ok, so we can simply compare against last_eb to figure out
	 * whether the path doesn't exist. This will only happen in
	 * the case that we're doing a tail append, so maybe we can
	 * take advantage of that information somehow.
	 */
	if (ocfs2_et_get_last_eb_blk(et) ==
	    path_leaf_bh(path)->b_blocknr) {
		/*
		 * Ok, ocfs2_find_path() returned us the rightmost
		 * tree path. This might be an appending insert. There are
		 * two cases:
		 *    1) We're doing a true append at the tail:
		 *	-This might even be off the end of the leaf
		 *    2) We're "appending" by rotating in the tail
		 */
		ocfs2_figure_appending_type(insert, el, insert_rec);
	}

out:
	ocfs2_free_path(path);

	if (ret == 0)
		*last_eb_bh = bh;
	else
		brelse(bh);
	return ret;
}