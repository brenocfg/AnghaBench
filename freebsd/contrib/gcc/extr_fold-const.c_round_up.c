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
typedef  scalar_t__ tree ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_AND_EXPR ; 
 int /*<<< orphan*/  CEIL_DIV_EXPR ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  MULT_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ multiple_of_p (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ size_binop (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

tree
round_up (tree value, int divisor)
{
  tree div = NULL_TREE;

  gcc_assert (divisor > 0);
  if (divisor == 1)
    return value;

  /* See if VALUE is already a multiple of DIVISOR.  If so, we don't
     have to do anything.  Only do this when we are not given a const,
     because in that case, this check is more expensive than just
     doing it.  */
  if (TREE_CODE (value) != INTEGER_CST)
    {
      div = build_int_cst (TREE_TYPE (value), divisor);

      if (multiple_of_p (TREE_TYPE (value), value, div))
	return value;
    }

  /* If divisor is a power of two, simplify this to bit manipulation.  */
  if (divisor == (divisor & -divisor))
    {
      tree t;

      t = build_int_cst (TREE_TYPE (value), divisor - 1);
      value = size_binop (PLUS_EXPR, value, t);
      t = build_int_cst (TREE_TYPE (value), -divisor);
      value = size_binop (BIT_AND_EXPR, value, t);
    }
  else
    {
      if (!div)
	div = build_int_cst (TREE_TYPE (value), divisor);
      value = size_binop (CEIL_DIV_EXPR, value, div);
      value = size_binop (MULT_EXPR, value, div);
    }

  return value;
}