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
struct ocfs2_extent_list {int /*<<< orphan*/  l_tree_depth; } ;
struct ocfs2_extent_block {struct ocfs2_extent_list h_list; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void find_leaf_ins(void *data, struct buffer_head *bh)
{
	struct ocfs2_extent_block *eb =(struct ocfs2_extent_block *)bh->b_data;
	struct ocfs2_extent_list *el = &eb->h_list;
	struct buffer_head **ret = data;

	/* We want to retain only the leaf block. */
	if (le16_to_cpu(el->l_tree_depth) == 0) {
		get_bh(bh);
		*ret = bh;
	}
}