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
 int /*<<< orphan*/  COMPLETE_OR_VOID_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CONVERT_EXPR ; 
 int /*<<< orphan*/  EXACT_DIV_EXPR ; 
 scalar_t__ FUNCTION_TYPE ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 scalar_t__ PLUS_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 scalar_t__ VOID_TYPE ; 
 int /*<<< orphan*/  build_binary_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_size_in_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_zero_node ; 
 scalar_t__ operand_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 int /*<<< orphan*/  ptrdiff_type_node ; 
 scalar_t__ warn_pointer_arith ; 

__attribute__((used)) static tree
pointer_diff (tree op0, tree op1)
{
  tree restype = ptrdiff_type_node;

  tree target_type = TREE_TYPE (TREE_TYPE (op0));
  tree con0, con1, lit0, lit1;
  tree orig_op1 = op1;

  if (pedantic || warn_pointer_arith)
    {
      if (TREE_CODE (target_type) == VOID_TYPE)
	pedwarn ("pointer of type %<void *%> used in subtraction");
      if (TREE_CODE (target_type) == FUNCTION_TYPE)
	pedwarn ("pointer to a function used in subtraction");
    }

  /* If the conversion to ptrdiff_type does anything like widening or
     converting a partial to an integral mode, we get a convert_expression
     that is in the way to do any simplifications.
     (fold-const.c doesn't know that the extra bits won't be needed.
     split_tree uses STRIP_SIGN_NOPS, which leaves conversions to a
     different mode in place.)
     So first try to find a common term here 'by hand'; we want to cover
     at least the cases that occur in legal static initializers.  */
  if ((TREE_CODE (op0) == NOP_EXPR || TREE_CODE (op0) == CONVERT_EXPR)
      && (TYPE_PRECISION (TREE_TYPE (op0))
	  == TYPE_PRECISION (TREE_TYPE (TREE_OPERAND (op0, 0)))))
    con0 = TREE_OPERAND (op0, 0);
  else
    con0 = op0;
  if ((TREE_CODE (op1) == NOP_EXPR || TREE_CODE (op1) == CONVERT_EXPR)
      && (TYPE_PRECISION (TREE_TYPE (op1))
	  == TYPE_PRECISION (TREE_TYPE (TREE_OPERAND (op1, 0)))))
    con1 = TREE_OPERAND (op1, 0);
  else
    con1 = op1;

  if (TREE_CODE (con0) == PLUS_EXPR)
    {
      lit0 = TREE_OPERAND (con0, 1);
      con0 = TREE_OPERAND (con0, 0);
    }
  else
    lit0 = integer_zero_node;

  if (TREE_CODE (con1) == PLUS_EXPR)
    {
      lit1 = TREE_OPERAND (con1, 1);
      con1 = TREE_OPERAND (con1, 0);
    }
  else
    lit1 = integer_zero_node;

  if (operand_equal_p (con0, con1, 0))
    {
      op0 = lit0;
      op1 = lit1;
    }


  /* First do the subtraction as integers;
     then drop through to build the divide operator.
     Do not do default conversions on the minus operator
     in case restype is a short type.  */

  op0 = build_binary_op (MINUS_EXPR, convert (restype, op0),
			 convert (restype, op1), 0);
  /* This generates an error if op1 is pointer to incomplete type.  */
  if (!COMPLETE_OR_VOID_TYPE_P (TREE_TYPE (TREE_TYPE (orig_op1))))
    error ("arithmetic on pointer to an incomplete type");

  /* This generates an error if op0 is pointer to incomplete type.  */
  op1 = c_size_in_bytes (target_type);

  /* Divide by the size, in easiest possible way.  */
  return fold_build2 (EXACT_DIV_EXPR, restype, op0, convert (restype, op1));
}