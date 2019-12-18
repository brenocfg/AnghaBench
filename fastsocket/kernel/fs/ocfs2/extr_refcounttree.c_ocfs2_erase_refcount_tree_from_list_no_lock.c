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
struct ocfs2_super {struct ocfs2_refcount_tree* osb_ref_tree_lru; int /*<<< orphan*/  osb_rf_lock_tree; } ;
struct ocfs2_refcount_tree {int /*<<< orphan*/  rf_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
ocfs2_erase_refcount_tree_from_list_no_lock(struct ocfs2_super *osb,
					struct ocfs2_refcount_tree *tree)
{
	rb_erase(&tree->rf_node, &osb->osb_rf_lock_tree);
	if (osb->osb_ref_tree_lru && osb->osb_ref_tree_lru == tree)
		osb->osb_ref_tree_lru = NULL;
}