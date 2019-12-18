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

/* Variables and functions */
 int /*<<< orphan*/  NODE_LEAF ; 
 scalar_t__* leaf_node_next_leaf (void*) ; 
 scalar_t__* leaf_node_num_cells (void*) ; 
 int /*<<< orphan*/  set_node_root (void*,int) ; 
 int /*<<< orphan*/  set_node_type (void*,int /*<<< orphan*/ ) ; 

void initialize_leaf_node(void* node) {
  set_node_type(node, NODE_LEAF);
  set_node_root(node, false);
  *leaf_node_num_cells(node) = 0;
  *leaf_node_next_leaf(node) = 0;  // 0 represents no sibling
}