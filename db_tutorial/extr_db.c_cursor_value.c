#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  cell_num; TYPE_1__* table; int /*<<< orphan*/  page_num; } ;
struct TYPE_4__ {int /*<<< orphan*/  pager; } ;
typedef  TYPE_2__ Cursor ;

/* Variables and functions */
 void* get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* leaf_node_value (void*,int /*<<< orphan*/ ) ; 

void* cursor_value(Cursor* cursor) {
  uint32_t page_num = cursor->page_num;
  void* page = get_page(cursor->table->pager, page_num);
  return leaf_node_value(page, cursor->cell_num);
}