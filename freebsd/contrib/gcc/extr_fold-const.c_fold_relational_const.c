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
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 scalar_t__ COMPLEX_CST ; 
#define  EQ_EXPR 141 
#define  GE_EXPR 140 
#define  GT_EXPR 139 
 scalar_t__ INTEGER_CST ; 
 int INT_CST_LT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INT_CST_LT_UNSIGNED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  LE_EXPR 138 
#define  LTGT_EXPR 137 
#define  LT_EXPR 136 
#define  NE_EXPR 135 
 int /*<<< orphan*/  NULL_TREE ; 
#define  ORDERED_EXPR 134 
 scalar_t__ REAL_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_IMAGPART (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_REALPART (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TREE_REAL_CST_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUTH_ANDIF_EXPR ; 
 int /*<<< orphan*/  TRUTH_ORIF_EXPR ; 
 scalar_t__ TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
#define  UNEQ_EXPR 133 
#define  UNGE_EXPR 132 
#define  UNGT_EXPR 131 
#define  UNLE_EXPR 130 
#define  UNLT_EXPR 129 
#define  UNORDERED_EXPR 128 
 int /*<<< orphan*/  constant_boolean_node (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_trapping_math ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int invert_tree_comparison (int,int) ; 
 int real_compare (int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ real_isnan (int /*<<< orphan*/  const*) ; 
 int swap_tree_comparison (int) ; 
 int tree_int_cst_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_relational_const (enum tree_code code, tree type, tree op0, tree op1)
{
  int result, invert;

  /* From here on, the only cases we handle are when the result is
     known to be a constant.  */

  if (TREE_CODE (op0) == REAL_CST && TREE_CODE (op1) == REAL_CST)
    {
      const REAL_VALUE_TYPE *c0 = TREE_REAL_CST_PTR (op0);
      const REAL_VALUE_TYPE *c1 = TREE_REAL_CST_PTR (op1);

      /* Handle the cases where either operand is a NaN.  */
      if (real_isnan (c0) || real_isnan (c1))
	{
	  switch (code)
	    {
	    case EQ_EXPR:
	    case ORDERED_EXPR:
	      result = 0;
	      break;

	    case NE_EXPR:
	    case UNORDERED_EXPR:
	    case UNLT_EXPR:
	    case UNLE_EXPR:
	    case UNGT_EXPR:
	    case UNGE_EXPR:
	    case UNEQ_EXPR:
              result = 1;
	      break;

	    case LT_EXPR:
	    case LE_EXPR:
	    case GT_EXPR:
	    case GE_EXPR:
	    case LTGT_EXPR:
	      if (flag_trapping_math)
		return NULL_TREE;
	      result = 0;
	      break;

	    default:
	      gcc_unreachable ();
	    }

	  return constant_boolean_node (result, type);
	}

      return constant_boolean_node (real_compare (code, c0, c1), type);
    }

  /* Handle equality/inequality of complex constants.  */
  if (TREE_CODE (op0) == COMPLEX_CST && TREE_CODE (op1) == COMPLEX_CST)
    {
      tree rcond = fold_relational_const (code, type,
					  TREE_REALPART (op0),
					  TREE_REALPART (op1));
      tree icond = fold_relational_const (code, type,
					  TREE_IMAGPART (op0),
					  TREE_IMAGPART (op1));
      if (code == EQ_EXPR)
	return fold_build2 (TRUTH_ANDIF_EXPR, type, rcond, icond);
      else if (code == NE_EXPR)
	return fold_build2 (TRUTH_ORIF_EXPR, type, rcond, icond);
      else
	return NULL_TREE;
    }

  /* From here on we only handle LT, LE, GT, GE, EQ and NE.

     To compute GT, swap the arguments and do LT.
     To compute GE, do LT and invert the result.
     To compute LE, swap the arguments, do LT and invert the result.
     To compute NE, do EQ and invert the result.

     Therefore, the code below must handle only EQ and LT.  */

  if (code == LE_EXPR || code == GT_EXPR)
    {
      tree tem = op0;
      op0 = op1;
      op1 = tem;
      code = swap_tree_comparison (code);
    }

  /* Note that it is safe to invert for real values here because we
     have already handled the one case that it matters.  */

  invert = 0;
  if (code == NE_EXPR || code == GE_EXPR)
    {
      invert = 1;
      code = invert_tree_comparison (code, false);
    }

  /* Compute a result for LT or EQ if args permit;
     Otherwise return T.  */
  if (TREE_CODE (op0) == INTEGER_CST && TREE_CODE (op1) == INTEGER_CST)
    {
      if (code == EQ_EXPR)
	result = tree_int_cst_equal (op0, op1);
      else if (TYPE_UNSIGNED (TREE_TYPE (op0)))
	result = INT_CST_LT_UNSIGNED (op0, op1);
      else
	result = INT_CST_LT (op0, op1);
    }
  else
    return NULL_TREE;

  if (invert)
    result ^= 1;
  return constant_boolean_node (result, type);
}