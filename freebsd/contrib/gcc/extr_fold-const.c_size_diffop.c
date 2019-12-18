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
 scalar_t__ INTEGER_CST ; 
 scalar_t__ INTEGER_TYPE ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_IS_SIZETYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (scalar_t__) ; 
 scalar_t__ bitsizetype ; 
 scalar_t__ build_int_cst (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ sbitsizetype ; 
 scalar_t__ size_binop (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ ssizetype ; 
 scalar_t__ tree_int_cst_equal (scalar_t__,scalar_t__) ; 
 scalar_t__ tree_int_cst_lt (scalar_t__,scalar_t__) ; 

tree
size_diffop (tree arg0, tree arg1)
{
  tree type = TREE_TYPE (arg0);
  tree ctype;

  gcc_assert (TREE_CODE (type) == INTEGER_TYPE && TYPE_IS_SIZETYPE (type)
	      && type == TREE_TYPE (arg1));

  /* If the type is already signed, just do the simple thing.  */
  if (!TYPE_UNSIGNED (type))
    return size_binop (MINUS_EXPR, arg0, arg1);

  ctype = type == bitsizetype ? sbitsizetype : ssizetype;

  /* If either operand is not a constant, do the conversions to the signed
     type and subtract.  The hardware will do the right thing with any
     overflow in the subtraction.  */
  if (TREE_CODE (arg0) != INTEGER_CST || TREE_CODE (arg1) != INTEGER_CST)
    return size_binop (MINUS_EXPR, fold_convert (ctype, arg0),
		       fold_convert (ctype, arg1));

  /* If ARG0 is larger than ARG1, subtract and return the result in CTYPE.
     Otherwise, subtract the other way, convert to CTYPE (we know that can't
     overflow) and negate (which can't either).  Special-case a result
     of zero while we're here.  */
  if (tree_int_cst_equal (arg0, arg1))
    return build_int_cst (ctype, 0);
  else if (tree_int_cst_lt (arg1, arg0))
    return fold_convert (ctype, size_binop (MINUS_EXPR, arg0, arg1));
  else
    return size_binop (MINUS_EXPR, build_int_cst (ctype, 0),
		       fold_convert (ctype, size_binop (MINUS_EXPR,
							arg1, arg0)));
}