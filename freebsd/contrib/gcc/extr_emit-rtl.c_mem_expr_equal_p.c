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
 scalar_t__ COMPONENT_REF ; 
 int /*<<< orphan*/  DECL_P (scalar_t__) ; 
 scalar_t__ INDIRECT_REF_P (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 

int
mem_expr_equal_p (tree expr1, tree expr2)
{
  if (expr1 == expr2)
    return 1;

  if (! expr1 || ! expr2)
    return 0;

  if (TREE_CODE (expr1) != TREE_CODE (expr2))
    return 0;

  if (TREE_CODE (expr1) == COMPONENT_REF)
    return 
      mem_expr_equal_p (TREE_OPERAND (expr1, 0),
			TREE_OPERAND (expr2, 0))
      && mem_expr_equal_p (TREE_OPERAND (expr1, 1), /* field decl */
			   TREE_OPERAND (expr2, 1));
  
  if (INDIRECT_REF_P (expr1))
    return mem_expr_equal_p (TREE_OPERAND (expr1, 0),
			     TREE_OPERAND (expr2, 0));

  /* ARRAY_REFs, ARRAY_RANGE_REFs and BIT_FIELD_REFs should already
	      have been resolved here.  */
  gcc_assert (DECL_P (expr1));
  
  /* Decls with different pointers can't be equal.  */
  return 0;
}