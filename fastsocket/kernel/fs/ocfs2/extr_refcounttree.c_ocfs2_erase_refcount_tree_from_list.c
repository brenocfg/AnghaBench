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
struct ocfs2_super {int /*<<< orphan*/  osb_lock; } ;
struct ocfs2_refcount_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_erase_refcount_tree_from_list_no_lock (struct ocfs2_super*,struct ocfs2_refcount_tree*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_erase_refcount_tree_from_list(struct ocfs2_super *osb,
					struct ocfs2_refcount_tree *tree)
{
	spin_lock(&osb->osb_lock);
	ocfs2_erase_refcount_tree_from_list_no_lock(osb, tree);
	spin_unlock(&osb->osb_lock);
}