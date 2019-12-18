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
struct radix_tree_root {int /*<<< orphan*/  rnode; } ;
struct radix_tree_node {int /*<<< orphan*/  height; } ;

/* Variables and functions */
 unsigned int __lookup (struct radix_tree_node*,void***,unsigned long*,unsigned long,unsigned int,unsigned long*) ; 
 struct radix_tree_node* indirect_to_ptr (struct radix_tree_node*) ; 
 int /*<<< orphan*/  radix_tree_is_indirect_ptr (struct radix_tree_node*) ; 
 unsigned long radix_tree_maxindex (int /*<<< orphan*/ ) ; 
 struct radix_tree_node* rcu_dereference (int /*<<< orphan*/ ) ; 

unsigned int
radix_tree_gang_lookup_slot(struct radix_tree_root *root,
			void ***results, unsigned long *indices,
			unsigned long first_index, unsigned int max_items)
{
	unsigned long max_index;
	struct radix_tree_node *node;
	unsigned long cur_index = first_index;
	unsigned int ret;

	node = rcu_dereference(root->rnode);
	if (!node)
		return 0;

	if (!radix_tree_is_indirect_ptr(node)) {
		if (first_index > 0)
			return 0;
		results[0] = (void **)&root->rnode;
		if (indices)
			indices[0] = 0;
		return 1;
	}
	node = indirect_to_ptr(node);

	max_index = radix_tree_maxindex(node->height);

	ret = 0;
	while (ret < max_items) {
		unsigned int slots_found;
		unsigned long next_index;	/* Index of next search */

		if (cur_index > max_index)
			break;
		slots_found = __lookup(node, results + ret,
				indices ? indices + ret : NULL,
				cur_index, max_items - ret, &next_index);
		ret += slots_found;
		if (next_index == 0)
			break;
		cur_index = next_index;
	}

	return ret;
}