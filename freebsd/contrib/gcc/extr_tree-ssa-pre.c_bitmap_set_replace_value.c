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
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_3__* bitmap_set_t ;
struct TYPE_9__ {int /*<<< orphan*/  expressions; } ;
struct TYPE_8__ {int /*<<< orphan*/  expr; struct TYPE_8__* next; } ;
struct TYPE_7__ {TYPE_2__* head; } ;

/* Variables and functions */
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 TYPE_1__* VALUE_HANDLE_EXPR_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ bitmap_bit_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_contains_value (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_gimple_min_invariant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bitmap_set_replace_value (bitmap_set_t set, tree lookfor, tree expr)
{
  value_set_t exprset;
  value_set_node_t node;
  if (is_gimple_min_invariant (lookfor))
    return;
  if (!bitmap_set_contains_value (set, lookfor))
    return;

  /* The number of expressions having a given value is usually
     significantly less than the total number of expressions in SET.
     Thus, rather than check, for each expression in SET, whether it
     has the value LOOKFOR, we walk the reverse mapping that tells us
     what expressions have a given value, and see if any of those
     expressions are in our set.  For large testcases, this is about
     5-10x faster than walking the bitmap.  If this is somehow a
     significant lose for some cases, we can choose which set to walk
     based on the set size.  */
  exprset = VALUE_HANDLE_EXPR_SET (lookfor);
  for (node = exprset->head; node; node = node->next)
    {
      if (TREE_CODE (node->expr) == SSA_NAME)
	{
	  if (bitmap_bit_p (set->expressions, SSA_NAME_VERSION (node->expr)))
	    {
	      bitmap_clear_bit (set->expressions, SSA_NAME_VERSION (node->expr));
	      bitmap_set_bit (set->expressions, SSA_NAME_VERSION (expr));
	      return;
	    }
	}
    }
}