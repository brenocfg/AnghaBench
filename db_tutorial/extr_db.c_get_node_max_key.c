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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
#define  NODE_INTERNAL 129 
#define  NODE_LEAF 128 
 int get_node_type (void*) ; 
 int /*<<< orphan*/ * internal_node_key (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * internal_node_num_keys (void*) ; 
 int /*<<< orphan*/ * leaf_node_key (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * leaf_node_num_cells (void*) ; 

uint32_t get_node_max_key(void* node) {
  switch (get_node_type(node)) {
    case NODE_INTERNAL:
      return *internal_node_key(node, *internal_node_num_keys(node) - 1);
    case NODE_LEAF:
      return *leaf_node_key(node, *leaf_node_num_cells(node) - 1);
  }
}