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
 scalar_t__ INTEGER_CST ; 
 scalar_t__ MINUS_EXPR ; 
 scalar_t__ PLUS_EXPR ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int is_gimple_min_invariant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
valid_value_p (tree expr)
{
  if (TREE_CODE (expr) == SSA_NAME)
    return true;

  if (TREE_CODE (expr) == PLUS_EXPR
      || TREE_CODE (expr) == MINUS_EXPR)
    return (TREE_CODE (TREE_OPERAND (expr, 0)) == SSA_NAME
	    && TREE_CODE (TREE_OPERAND (expr, 1)) == INTEGER_CST);
  
  return is_gimple_min_invariant (expr);
}