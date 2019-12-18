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
typedef  void* u64 ;
struct rb_node {int dummy; } ;
struct extent_state {struct extent_io_tree* tree; int /*<<< orphan*/  rb_node; void* end; void* start; int /*<<< orphan*/  state; } ;
struct extent_io_tree {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  free_extent_state (struct extent_state*) ; 
 int /*<<< orphan*/  split_cb (struct extent_io_tree*,struct extent_state*,void*) ; 
 struct rb_node* tree_insert (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int split_state(struct extent_io_tree *tree, struct extent_state *orig,
		       struct extent_state *prealloc, u64 split)
{
	struct rb_node *node;

	split_cb(tree, orig, split);

	prealloc->start = orig->start;
	prealloc->end = split - 1;
	prealloc->state = orig->state;
	orig->start = split;

	node = tree_insert(&tree->state, prealloc->end, &prealloc->rb_node);
	if (node) {
		free_extent_state(prealloc);
		return -EEXIST;
	}
	prealloc->tree = tree;
	return 0;
}