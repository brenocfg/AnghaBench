#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ root_page_num; TYPE_2__* pager; } ;
typedef  TYPE_1__ Table ;
struct TYPE_8__ {scalar_t__ num_pages; } ;
typedef  TYPE_2__ Pager ;

/* Variables and functions */
 void* get_page (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialize_leaf_node (void*) ; 
 TYPE_1__* malloc (int) ; 
 TYPE_2__* pager_open (char const*) ; 
 int /*<<< orphan*/  set_node_root (void*,int) ; 

Table* db_open(const char* filename) {
  Pager* pager = pager_open(filename);

  Table* table = malloc(sizeof(Table));
  table->pager = pager;
  table->root_page_num = 0;

  if (pager->num_pages == 0) {
    // New database file. Initialize page 0 as leaf node.
    void* root_node = get_page(pager, 0);
    initialize_leaf_node(root_node);
    set_node_root(root_node, true);
  }

  return table;
}