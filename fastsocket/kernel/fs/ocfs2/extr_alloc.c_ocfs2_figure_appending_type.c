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
struct ocfs2_insert_type {int /*<<< orphan*/  ins_appending; } ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_leaf_clusters; int /*<<< orphan*/  e_cpos; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; int /*<<< orphan*/  l_next_free_rec; int /*<<< orphan*/  l_tree_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND_NONE ; 
 int /*<<< orphan*/  APPEND_TAIL ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_is_empty_extent (struct ocfs2_extent_rec*) ; 

__attribute__((used)) static void ocfs2_figure_appending_type(struct ocfs2_insert_type *insert,
					struct ocfs2_extent_list *el,
					struct ocfs2_extent_rec *insert_rec)
{
	int i;
	u32 cpos = le32_to_cpu(insert_rec->e_cpos);
	struct ocfs2_extent_rec *rec;

	insert->ins_appending = APPEND_NONE;

	BUG_ON(le16_to_cpu(el->l_tree_depth) != 0);

	if (!el->l_next_free_rec)
		goto set_tail_append;

	if (ocfs2_is_empty_extent(&el->l_recs[0])) {
		/* Were all records empty? */
		if (le16_to_cpu(el->l_next_free_rec) == 1)
			goto set_tail_append;
	}

	i = le16_to_cpu(el->l_next_free_rec) - 1;
	rec = &el->l_recs[i];

	if (cpos >=
	    (le32_to_cpu(rec->e_cpos) + le16_to_cpu(rec->e_leaf_clusters)))
		goto set_tail_append;

	return;

set_tail_append:
	insert->ins_appending = APPEND_TAIL;
}