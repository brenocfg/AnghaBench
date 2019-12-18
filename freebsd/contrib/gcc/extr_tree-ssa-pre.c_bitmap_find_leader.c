#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* value_set_t ;
typedef  TYPE_2__* value_set_node_t ;
typedef  int /*<<< orphan*/ * tree ;
typedef  TYPE_3__* bitmap_set_t ;
struct TYPE_9__ {int /*<<< orphan*/  expressions; } ;
struct TYPE_8__ {int /*<<< orphan*/ * expr; struct TYPE_8__* next; } ;
struct TYPE_7__ {TYPE_2__* head; } ;

/* Variables and functions */
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_VERSION (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 TYPE_1__* VALUE_HANDLE_EXPR_SET (int /*<<< orphan*/ *) ; 
 scalar_t__ bitmap_bit_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bitmap_set_contains_value (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_gimple_min_invariant (int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
bitmap_find_leader (bitmap_set_t set, tree val)
{
  if (val == NULL)
    return NULL;

  if (is_gimple_min_invariant (val))
    return val;
  if (bitmap_set_contains_value (set, val))
    {
      /* Rather than walk the entire bitmap of expressions, and see
	 whether any of them has the value we are looking for, we look
	 at the reverse mapping, which tells us the set of expressions
	 that have a given value (IE value->expressions with that
	 value) and see if any of those expressions are in our set.
	 The number of expressions per value is usually significantly
	 less than the number of expressions in the set.  In fact, for
	 large testcases, doing it this way is roughly 5-10x faster
	 than walking the bitmap.
	 If this is somehow a significant lose for some cases, we can
	 choose which set to walk based on which set is smaller.  */
      value_set_t exprset;
      value_set_node_t node;
      exprset = VALUE_HANDLE_EXPR_SET (val);
      for (node = exprset->head; node; node = node->next)
	{
	  if (TREE_CODE (node->expr) == SSA_NAME)
	    {
	      if (bitmap_bit_p (set->expressions,
				SSA_NAME_VERSION (node->expr)))
		return node->expr;
	    }
	}
    }
  return NULL;
}