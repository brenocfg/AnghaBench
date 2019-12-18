#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* value_set_t ;
typedef  TYPE_2__* value_set_node_t ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_7__ {int /*<<< orphan*/  expr; struct TYPE_7__* next; } ;
struct TYPE_6__ {TYPE_2__* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_remove (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valid_in_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
clean (value_set_t set, basic_block block)
{
  value_set_node_t node;
  value_set_node_t next;
  node = set->head;
  while (node)
    {
      next = node->next;
      if (!valid_in_set (set, node->expr, block))
	set_remove (set, node->expr);
      node = next;
    }
}