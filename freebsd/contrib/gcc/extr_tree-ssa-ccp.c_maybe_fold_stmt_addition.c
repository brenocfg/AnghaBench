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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ ARRAY_REF ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ MINUS_EXPR ; 
 scalar_t__ MULT_EXPR ; 
 int /*<<< orphan*/  NEGATE_EXPR ; 
 int /*<<< orphan*/ * NULL_TREE ; 
 scalar_t__ PLUS_EXPR ; 
 int /*<<< orphan*/  POINTER_TYPE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_DOMAIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_MIN_VALUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_SIZE_UNIT (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPE_UNSIGNED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build1 (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fold_convert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fold_unary (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * int_const_binop (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_zerop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * maybe_fold_offset_to_array_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * maybe_fold_offset_to_component_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sizetype ; 
 scalar_t__ tree_int_cst_lt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
maybe_fold_stmt_addition (tree expr)
{
  tree op0 = TREE_OPERAND (expr, 0);
  tree op1 = TREE_OPERAND (expr, 1);
  tree ptr_type = TREE_TYPE (expr);
  tree ptd_type;
  tree t;
  bool subtract = (TREE_CODE (expr) == MINUS_EXPR);

  /* We're only interested in pointer arithmetic.  */
  if (!POINTER_TYPE_P (ptr_type))
    return NULL_TREE;
  /* Canonicalize the integral operand to op1.  */
  if (INTEGRAL_TYPE_P (TREE_TYPE (op0)))
    {
      if (subtract)
	return NULL_TREE;
      t = op0, op0 = op1, op1 = t;
    }
  /* It had better be a constant.  */
  if (TREE_CODE (op1) != INTEGER_CST)
    return NULL_TREE;
  /* The first operand should be an ADDR_EXPR.  */
  if (TREE_CODE (op0) != ADDR_EXPR)
    return NULL_TREE;
  op0 = TREE_OPERAND (op0, 0);

  /* If the first operand is an ARRAY_REF, expand it so that we can fold
     the offset into it.  */
  while (TREE_CODE (op0) == ARRAY_REF)
    {
      tree array_obj = TREE_OPERAND (op0, 0);
      tree array_idx = TREE_OPERAND (op0, 1);
      tree elt_type = TREE_TYPE (op0);
      tree elt_size = TYPE_SIZE_UNIT (elt_type);
      tree min_idx;

      if (TREE_CODE (array_idx) != INTEGER_CST)
	break;
      if (TREE_CODE (elt_size) != INTEGER_CST)
	break;

      /* Un-bias the index by the min index of the array type.  */
      min_idx = TYPE_DOMAIN (TREE_TYPE (array_obj));
      if (min_idx)
	{
	  min_idx = TYPE_MIN_VALUE (min_idx);
	  if (min_idx)
	    {
	      if (TREE_CODE (min_idx) != INTEGER_CST)
		break;

	      array_idx = fold_convert (TREE_TYPE (min_idx), array_idx);
	      if (!integer_zerop (min_idx))
		array_idx = int_const_binop (MINUS_EXPR, array_idx,
					     min_idx, 0);
	    }
	}

      /* Convert the index to a byte offset.  */
      array_idx = fold_convert (sizetype, array_idx);
      array_idx = int_const_binop (MULT_EXPR, array_idx, elt_size, 0);

      /* Update the operands for the next round, or for folding.  */
      /* If we're manipulating unsigned types, then folding into negative
	 values can produce incorrect results.  Particularly if the type
	 is smaller than the width of the pointer.  */
      if (subtract
	  && TYPE_UNSIGNED (TREE_TYPE (op1))
	  && tree_int_cst_lt (array_idx, op1))
	return NULL;
      op1 = int_const_binop (subtract ? MINUS_EXPR : PLUS_EXPR,
			     array_idx, op1, 0);
      subtract = false;
      op0 = array_obj;
    }

  /* If we weren't able to fold the subtraction into another array reference,
     canonicalize the integer for passing to the array and component ref
     simplification functions.  */
  if (subtract)
    {
      if (TYPE_UNSIGNED (TREE_TYPE (op1)))
	return NULL;
      op1 = fold_unary (NEGATE_EXPR, TREE_TYPE (op1), op1);
      /* ??? In theory fold should always produce another integer.  */
      if (op1 == NULL || TREE_CODE (op1) != INTEGER_CST)
	return NULL;
    }

  ptd_type = TREE_TYPE (ptr_type);

  /* At which point we can try some of the same things as for indirects.  */
  t = maybe_fold_offset_to_array_ref (op0, op1, ptd_type);
  if (!t)
    t = maybe_fold_offset_to_component_ref (TREE_TYPE (op0), op0, op1,
					    ptd_type, false);
  if (t)
    t = build1 (ADDR_EXPR, ptr_type, t);

  return t;
}