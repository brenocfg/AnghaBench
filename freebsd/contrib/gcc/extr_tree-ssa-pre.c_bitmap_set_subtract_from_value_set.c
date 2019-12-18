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
typedef  TYPE_1__* value_set_t ;
typedef  TYPE_2__* value_set_node_t ;
typedef  int /*<<< orphan*/  bitmap_set_t ;
struct TYPE_8__ {int /*<<< orphan*/  expr; struct TYPE_8__* next; } ;
struct TYPE_7__ {TYPE_2__* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_set_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_into_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* set_new (int) ; 

__attribute__((used)) static value_set_t
bitmap_set_subtract_from_value_set (value_set_t a, bitmap_set_t b,
				    bool indexed)
{
  value_set_t ret = set_new (indexed);
  value_set_node_t node;
  for (node = a->head;
       node;
       node = node->next)
    {
      if (!bitmap_set_contains (b, node->expr))
	insert_into_set (ret, node->expr);
    }
  return ret;
}