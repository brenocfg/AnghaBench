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
typedef  int /*<<< orphan*/  tree_t ;
typedef  int /*<<< orphan*/  node_t ;

/* Variables and functions */
 int /*<<< orphan*/  node_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * tree_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static node_t *
remove_iterate_cb(tree_t *tree, node_t *node, void *data)
{
	unsigned *nnodes = (unsigned *)data;
	node_t *ret = tree_next(tree, node);

	node_remove(tree, node, *nnodes);

	return (ret);
}