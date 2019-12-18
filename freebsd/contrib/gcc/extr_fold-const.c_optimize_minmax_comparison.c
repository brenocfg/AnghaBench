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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
#define  EQ_EXPR 133 
#define  GE_EXPR 132 
#define  GT_EXPR 131 
 scalar_t__ INTEGER_CST ; 
#define  LE_EXPR 130 
#define  LT_EXPR 129 
 int MAX_EXPR ; 
 int MIN_EXPR ; 
#define  NE_EXPR 128 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  STRIP_SIGN_NOPS (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CONSTANT_OVERFLOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int const TRUTH_ORIF_EXPR ; 
 int /*<<< orphan*/  fold_build2 (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int invert_tree_comparison (int,int) ; 
 int /*<<< orphan*/  invert_truthvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omit_one_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tree_int_cst_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tree_int_cst_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
optimize_minmax_comparison (enum tree_code code, tree type, tree op0, tree op1)
{
  tree arg0 = op0;
  enum tree_code op_code;
  tree comp_const = op1;
  tree minmax_const;
  int consts_equal, consts_lt;
  tree inner;

  STRIP_SIGN_NOPS (arg0);

  op_code = TREE_CODE (arg0);
  minmax_const = TREE_OPERAND (arg0, 1);
  consts_equal = tree_int_cst_equal (minmax_const, comp_const);
  consts_lt = tree_int_cst_lt (minmax_const, comp_const);
  inner = TREE_OPERAND (arg0, 0);

  /* If something does not permit us to optimize, return the original tree.  */
  if ((op_code != MIN_EXPR && op_code != MAX_EXPR)
      || TREE_CODE (comp_const) != INTEGER_CST
      || TREE_CONSTANT_OVERFLOW (comp_const)
      || TREE_CODE (minmax_const) != INTEGER_CST
      || TREE_CONSTANT_OVERFLOW (minmax_const))
    return NULL_TREE;

  /* Now handle all the various comparison codes.  We only handle EQ_EXPR
     and GT_EXPR, doing the rest with recursive calls using logical
     simplifications.  */
  switch (code)
    {
    case NE_EXPR:  case LT_EXPR:  case LE_EXPR:
      {
	tree tem = optimize_minmax_comparison (invert_tree_comparison (code, false),
					  type, op0, op1);
	if (tem)
	  return invert_truthvalue (tem);
	return NULL_TREE;
      }

    case GE_EXPR:
      return
	fold_build2 (TRUTH_ORIF_EXPR, type,
		     optimize_minmax_comparison
		     (EQ_EXPR, type, arg0, comp_const),
		     optimize_minmax_comparison
		     (GT_EXPR, type, arg0, comp_const));

    case EQ_EXPR:
      if (op_code == MAX_EXPR && consts_equal)
	/* MAX (X, 0) == 0  ->  X <= 0  */
	return fold_build2 (LE_EXPR, type, inner, comp_const);

      else if (op_code == MAX_EXPR && consts_lt)
	/* MAX (X, 0) == 5  ->  X == 5   */
	return fold_build2 (EQ_EXPR, type, inner, comp_const);

      else if (op_code == MAX_EXPR)
	/* MAX (X, 0) == -1  ->  false  */
	return omit_one_operand (type, integer_zero_node, inner);

      else if (consts_equal)
	/* MIN (X, 0) == 0  ->  X >= 0  */
	return fold_build2 (GE_EXPR, type, inner, comp_const);

      else if (consts_lt)
	/* MIN (X, 0) == 5  ->  false  */
	return omit_one_operand (type, integer_zero_node, inner);

      else
	/* MIN (X, 0) == -1  ->  X == -1  */
	return fold_build2 (EQ_EXPR, type, inner, comp_const);

    case GT_EXPR:
      if (op_code == MAX_EXPR && (consts_equal || consts_lt))
	/* MAX (X, 0) > 0  ->  X > 0
	   MAX (X, 0) > 5  ->  X > 5  */
	return fold_build2 (GT_EXPR, type, inner, comp_const);

      else if (op_code == MAX_EXPR)
	/* MAX (X, 0) > -1  ->  true  */
	return omit_one_operand (type, integer_one_node, inner);

      else if (op_code == MIN_EXPR && (consts_equal || consts_lt))
	/* MIN (X, 0) > 0  ->  false
	   MIN (X, 0) > 5  ->  false  */
	return omit_one_operand (type, integer_zero_node, inner);

      else
	/* MIN (X, 0) > -1  ->  X > -1  */
	return fold_build2 (GT_EXPR, type, inner, comp_const);

    default:
      return NULL_TREE;
    }
}