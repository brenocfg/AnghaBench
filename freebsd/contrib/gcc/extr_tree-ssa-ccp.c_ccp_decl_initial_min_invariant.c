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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handled_component_p (int /*<<< orphan*/ ) ; 
 scalar_t__ is_gimple_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_min_invariant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ccp_decl_initial_min_invariant (tree t)
{
  if (!is_gimple_min_invariant (t))
    return false;
  if (TREE_CODE (t) == ADDR_EXPR)
    {
      /* Inline and unroll is_gimple_addressable.  */
      while (1)
	{
	  t = TREE_OPERAND (t, 0);
	  if (is_gimple_id (t))
	    return true;
	  if (!handled_component_p (t))
	    return false;
	}
    }
  return true;
}