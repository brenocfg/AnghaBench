#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  pager; } ;
typedef  TYPE_1__ Table ;
typedef  int /*<<< orphan*/  Cursor ;

/* Variables and functions */
#define  NODE_INTERNAL 129 
#define  NODE_LEAF 128 
 int get_node_type (void*) ; 
 void* get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * internal_node_child (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  internal_node_find_child (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * leaf_node_find (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Cursor* internal_node_find(Table* table, uint32_t page_num, uint32_t key) {
  void* node = get_page(table->pager, page_num);

  uint32_t child_index = internal_node_find_child(node, key);
  uint32_t child_num = *internal_node_child(node, child_index);
  void* child = get_page(table->pager, child_num);
  switch (get_node_type(child)) {
    case NODE_LEAF:
      return leaf_node_find(table, child_num, key);
    case NODE_INTERNAL:
      return internal_node_find(table, child_num, key);
  }
}