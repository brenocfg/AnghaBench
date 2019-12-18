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
typedef  scalar_t__ tree ;
struct TYPE_7__ {scalar_t__ expr; struct TYPE_7__* next; } ;
struct TYPE_6__ {TYPE_2__* tail; TYPE_2__* head; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_value_handle (scalar_t__) ; 
 int /*<<< orphan*/  pool_free (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  value_remove_from_set_bitmap (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_set_node_pool ; 

__attribute__((used)) static void
set_remove (value_set_t set, tree expr)
{
  value_set_node_t node, prev;

  /* Remove the value of EXPR from the bitmap, decrement the set
     length, and remove it from the actual double linked list.  */
  value_remove_from_set_bitmap (set, get_value_handle (expr));
  set->length--;
  prev = NULL;
  for (node = set->head;
       node != NULL;
       prev = node, node = node->next)
    {
      if (node->expr == expr)
	{
	  if (prev == NULL)
	    set->head = node->next;
	  else
	    prev->next= node->next;

	  if (node == set->tail)
	    set->tail = prev;
	  pool_free (value_set_node_pool, node);
	  return;
	}
    }
}