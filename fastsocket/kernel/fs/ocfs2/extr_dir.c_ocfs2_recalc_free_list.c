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
struct ocfs2_dir_lookup_result {int /*<<< orphan*/  dl_leaf_bh; } ;
struct ocfs2_dir_block_trailer {int /*<<< orphan*/  db_free_rec_len; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int ocfs2_find_max_rec_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_remove_block_from_free_list (struct inode*,int /*<<< orphan*/ *,struct ocfs2_dir_lookup_result*) ; 
 struct ocfs2_dir_block_trailer* ocfs2_trailer_from_bh (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_recalc_free_list(struct inode *dir, handle_t *handle,
				   struct ocfs2_dir_lookup_result *lookup)
{
	int max_rec_len;
	struct ocfs2_dir_block_trailer *trailer;

	/* Walk dl_leaf_bh to figure out what the new free rec_len is. */
	max_rec_len = ocfs2_find_max_rec_len(dir->i_sb, lookup->dl_leaf_bh);
	if (max_rec_len) {
		/*
		 * There's still room in this block, so no need to remove it
		 * from the free list. In this case, we just want to update
		 * the rec len accounting.
		 */
		trailer = ocfs2_trailer_from_bh(lookup->dl_leaf_bh, dir->i_sb);
		trailer->db_free_rec_len = cpu_to_le16(max_rec_len);
		ocfs2_journal_dirty(handle, lookup->dl_leaf_bh);
	} else {
		ocfs2_remove_block_from_free_list(dir, handle, lookup);
	}
}