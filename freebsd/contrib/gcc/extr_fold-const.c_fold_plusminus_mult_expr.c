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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ MULT_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_INT_CST_LOW (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ build_int_cst (scalar_t__,scalar_t__) ; 
 scalar_t__ build_one_cst (scalar_t__) ; 
 scalar_t__ exact_log2 (scalar_t__) ; 
 scalar_t__ fold_build2 (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 scalar_t__ host_integerp (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ operand_equal_p (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_plusminus_mult_expr (enum tree_code code, tree type, tree arg0, tree arg1)
{
  tree arg00, arg01, arg10, arg11;
  tree alt0 = NULL_TREE, alt1 = NULL_TREE, same;

  /* (A * C) +- (B * C) -> (A+-B) * C.
     (A * C) +- A -> A * (C+-1).
     We are most concerned about the case where C is a constant,
     but other combinations show up during loop reduction.  Since
     it is not difficult, try all four possibilities.  */

  if (TREE_CODE (arg0) == MULT_EXPR)
    {
      arg00 = TREE_OPERAND (arg0, 0);
      arg01 = TREE_OPERAND (arg0, 1);
    }
  else
    {
      arg00 = arg0;
      arg01 = build_one_cst (type);
    }
  if (TREE_CODE (arg1) == MULT_EXPR)
    {
      arg10 = TREE_OPERAND (arg1, 0);
      arg11 = TREE_OPERAND (arg1, 1);
    }
  else
    {
      arg10 = arg1;
      arg11 = build_one_cst (type);
    }
  same = NULL_TREE;

  if (operand_equal_p (arg01, arg11, 0))
    same = arg01, alt0 = arg00, alt1 = arg10;
  else if (operand_equal_p (arg00, arg10, 0))
    same = arg00, alt0 = arg01, alt1 = arg11;
  else if (operand_equal_p (arg00, arg11, 0))
    same = arg00, alt0 = arg01, alt1 = arg10;
  else if (operand_equal_p (arg01, arg10, 0))
    same = arg01, alt0 = arg00, alt1 = arg11;

  /* No identical multiplicands; see if we can find a common
     power-of-two factor in non-power-of-two multiplies.  This
     can help in multi-dimensional array access.  */
  else if (host_integerp (arg01, 0)
	   && host_integerp (arg11, 0))
    {
      HOST_WIDE_INT int01, int11, tmp;
      bool swap = false;
      tree maybe_same;
      int01 = TREE_INT_CST_LOW (arg01);
      int11 = TREE_INT_CST_LOW (arg11);

      /* Move min of absolute values to int11.  */
      if ((int01 >= 0 ? int01 : -int01)
	  < (int11 >= 0 ? int11 : -int11))
        {
	  tmp = int01, int01 = int11, int11 = tmp;
	  alt0 = arg00, arg00 = arg10, arg10 = alt0;
	  maybe_same = arg01;
	  swap = true;
	}
      else
	maybe_same = arg11;

      if (exact_log2 (int11) > 0 && int01 % int11 == 0)
        {
	  alt0 = fold_build2 (MULT_EXPR, TREE_TYPE (arg00), arg00,
			      build_int_cst (TREE_TYPE (arg00),
					     int01 / int11));
	  alt1 = arg10;
	  same = maybe_same;
	  if (swap)
	    maybe_same = alt0, alt0 = alt1, alt1 = maybe_same;
	}
    }

  if (same)
    return fold_build2 (MULT_EXPR, type,
			fold_build2 (code, type,
				     fold_convert (type, alt0),
				     fold_convert (type, alt1)),
			fold_convert (type, same));

  return NULL_TREE;
}