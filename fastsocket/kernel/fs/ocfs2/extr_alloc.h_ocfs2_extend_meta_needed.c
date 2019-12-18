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

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ocfs2_extend_meta_needed(struct ocfs2_extent_list *root_el)
{
	/*
	 * Rather than do all the work of determining how much we need
	 * (involves a ton of reads and locks), just ask for the
	 * maximal limit.  That's a tree depth shift.  So, one block for
	 * level of the tree (current l_tree_depth), one block for the
	 * new tree_depth==0 extent_block, and one block at the new
	 * top-of-the tree.
	 */
	return le16_to_cpu(root_el->l_tree_depth) + 2;
}