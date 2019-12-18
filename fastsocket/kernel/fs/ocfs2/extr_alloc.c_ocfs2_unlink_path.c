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
struct ocfs2_path {TYPE_1__* p_node; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; } ;
struct ocfs2_extent_rec {int dummy; } ;
struct ocfs2_extent_list {int /*<<< orphan*/ * l_recs; scalar_t__ l_next_free_rec; } ;
struct ocfs2_extent_block {int /*<<< orphan*/  h_blkno; struct ocfs2_extent_list h_list; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {struct buffer_head* bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_ERROR ; 
 int le16_to_cpu (scalar_t__) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_cache_extent_block_free (struct ocfs2_cached_dealloc_ctxt*,struct ocfs2_extent_block*) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 scalar_t__ ocfs2_metadata_cache_owner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_remove_from_cache (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int path_num_items (struct ocfs2_path*) ; 

__attribute__((used)) static void ocfs2_unlink_path(handle_t *handle,
			      struct ocfs2_extent_tree *et,
			      struct ocfs2_cached_dealloc_ctxt *dealloc,
			      struct ocfs2_path *path, int unlink_start)
{
	int ret, i;
	struct ocfs2_extent_block *eb;
	struct ocfs2_extent_list *el;
	struct buffer_head *bh;

	for(i = unlink_start; i < path_num_items(path); i++) {
		bh = path->p_node[i].bh;

		eb = (struct ocfs2_extent_block *)bh->b_data;
		/*
		 * Not all nodes might have had their final count
		 * decremented by the caller - handle this here.
		 */
		el = &eb->h_list;
		if (le16_to_cpu(el->l_next_free_rec) > 1) {
			mlog(ML_ERROR,
			     "Inode %llu, attempted to remove extent block "
			     "%llu with %u records\n",
			     (unsigned long long)ocfs2_metadata_cache_owner(et->et_ci),
			     (unsigned long long)le64_to_cpu(eb->h_blkno),
			     le16_to_cpu(el->l_next_free_rec));

			ocfs2_journal_dirty(handle, bh);
			ocfs2_remove_from_cache(et->et_ci, bh);
			continue;
		}

		el->l_next_free_rec = 0;
		memset(&el->l_recs[0], 0, sizeof(struct ocfs2_extent_rec));

		ocfs2_journal_dirty(handle, bh);

		ret = ocfs2_cache_extent_block_free(dealloc, eb);
		if (ret)
			mlog_errno(ret);

		ocfs2_remove_from_cache(et->et_ci, bh);
	}
}