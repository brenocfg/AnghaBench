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
struct radix_tree_root {int height; int /*<<< orphan*/ * rnode; } ;
struct radix_tree_node {unsigned int height; int count; int /*<<< orphan*/ * slots; } ;

/* Variables and functions */
 int ENOMEM ; 
 int RADIX_TREE_MAX_TAGS ; 
 int /*<<< orphan*/  indirect_to_ptr (int /*<<< orphan*/ *) ; 
 struct radix_tree_node* ptr_to_indirect (struct radix_tree_node*) ; 
 unsigned long radix_tree_maxindex (unsigned int) ; 
 struct radix_tree_node* radix_tree_node_alloc (struct radix_tree_root*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ *,struct radix_tree_node*) ; 
 scalar_t__ root_tag_get (struct radix_tree_root*,int) ; 
 int /*<<< orphan*/  tag_set (struct radix_tree_node*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int radix_tree_extend(struct radix_tree_root *root, unsigned long index)
{
	struct radix_tree_node *node;
	unsigned int height;
	int tag;

	/* Figure out what the height should be.  */
	height = root->height + 1;
	while (index > radix_tree_maxindex(height))
		height++;

	if (root->rnode == NULL) {
		root->height = height;
		goto out;
	}

	do {
		unsigned int newheight;
		if (!(node = radix_tree_node_alloc(root)))
			return -ENOMEM;

		/* Increase the height.  */
		node->slots[0] = indirect_to_ptr(root->rnode);

		/* Propagate the aggregated tag info into the new root */
		for (tag = 0; tag < RADIX_TREE_MAX_TAGS; tag++) {
			if (root_tag_get(root, tag))
				tag_set(node, tag, 0);
		}

		newheight = root->height+1;
		node->height = newheight;
		node->count = 1;
		node = ptr_to_indirect(node);
		rcu_assign_pointer(root->rnode, node);
		root->height = newheight;
	} while (height > root->height);
out:
	return 0;
}