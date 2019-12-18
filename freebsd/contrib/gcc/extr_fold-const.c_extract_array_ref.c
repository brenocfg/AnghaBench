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
 scalar_t__ ARRAY_REF ; 
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ MULT_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ PLUS_EXPR ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ SSA_VAR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRIP_NOPS (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_ref_element_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
extract_array_ref (tree expr, tree *base, tree *offset)
{
  /* One canonical form is a PLUS_EXPR with the first
     argument being an ADDR_EXPR with a possible NOP_EXPR
     attached.  */
  if (TREE_CODE (expr) == PLUS_EXPR)
    {
      tree op0 = TREE_OPERAND (expr, 0);
      tree inner_base, dummy1;
      /* Strip NOP_EXPRs here because the C frontends and/or
	 folders present us (int *)&x.a + 4B possibly.  */
      STRIP_NOPS (op0);
      if (extract_array_ref (op0, &inner_base, &dummy1))
	{
	  *base = inner_base;
	  if (dummy1 == NULL_TREE)
	    *offset = TREE_OPERAND (expr, 1);
	  else
	    *offset = fold_build2 (PLUS_EXPR, TREE_TYPE (expr),
				   dummy1, TREE_OPERAND (expr, 1));
	  return true;
	}
    }
  /* Other canonical form is an ADDR_EXPR of an ARRAY_REF,
     which we transform into an ADDR_EXPR with appropriate
     offset.  For other arguments to the ADDR_EXPR we assume
     zero offset and as such do not care about the ADDR_EXPR
     type and strip possible nops from it.  */
  else if (TREE_CODE (expr) == ADDR_EXPR)
    {
      tree op0 = TREE_OPERAND (expr, 0);
      if (TREE_CODE (op0) == ARRAY_REF)
	{
	  tree idx = TREE_OPERAND (op0, 1);
	  *base = TREE_OPERAND (op0, 0);
	  *offset = fold_build2 (MULT_EXPR, TREE_TYPE (idx), idx,
				 array_ref_element_size (op0)); 
	}
      else
	{
	  /* Handle array-to-pointer decay as &a.  */
	  if (TREE_CODE (TREE_TYPE (op0)) == ARRAY_TYPE)
	    *base = TREE_OPERAND (expr, 0);
	  else
	    *base = expr;
	  *offset = NULL_TREE;
	}
      return true;
    }
  /* The next canonical form is a VAR_DECL with POINTER_TYPE.  */
  else if (SSA_VAR_P (expr)
	   && TREE_CODE (TREE_TYPE (expr)) == POINTER_TYPE)
    {
      *base = expr;
      *offset = NULL_TREE;
      return true;
    }

  return false;
}