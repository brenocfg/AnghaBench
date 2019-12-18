#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* value_set_t ;
typedef  TYPE_2__* value_set_node_t ;
typedef  int /*<<< orphan*/ * tree ;
struct TYPE_6__ {int /*<<< orphan*/ * expr; struct TYPE_6__* next; } ;
struct TYPE_5__ {scalar_t__ length; TYPE_2__* head; } ;

/* Variables and functions */
 int /*<<< orphan*/ * get_value_handle (int /*<<< orphan*/ *) ; 
 scalar_t__ is_gimple_min_invariant (int /*<<< orphan*/ *) ; 
 scalar_t__ value_exists_in_set_bitmap (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
find_leader (value_set_t set, tree val)
{
  value_set_node_t node;

  if (val == NULL)
    return NULL;

  /* Constants represent themselves.  */
  if (is_gimple_min_invariant (val))
    return val;

  if (set->length == 0)
    return NULL;

  if (value_exists_in_set_bitmap (set, val))
    {
      for (node = set->head;
	   node;
	   node = node->next)
	{
	  if (get_value_handle (node->expr) == val)
	    return node->expr;
	}
    }

  return NULL;
}