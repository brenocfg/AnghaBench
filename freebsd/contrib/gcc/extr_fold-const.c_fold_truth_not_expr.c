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
#define  BIT_AND_EXPR 143 
 int const BOOLEAN_TYPE ; 
#define  CLEANUP_POINT_EXPR 142 
#define  COMPOUND_EXPR 141 
#define  COND_EXPR 140 
#define  CONVERT_EXPR 139 
 int EQ_EXPR ; 
 int ERROR_MARK ; 
#define  FLOAT_EXPR 138 
 scalar_t__ FLOAT_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HONOR_NANS (int /*<<< orphan*/ ) ; 
#define  INTEGER_CST 137 
 int NE_EXPR ; 
#define  NON_LVALUE_EXPR 136 
#define  NOP_EXPR 135 
 int /*<<< orphan*/  NULL_TREE ; 
 int ORDERED_EXPR ; 
#define  SAVE_EXPR 134 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE_CLASS (int) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
#define  TRUTH_ANDIF_EXPR 133 
#define  TRUTH_AND_EXPR 132 
#define  TRUTH_NOT_EXPR 131 
#define  TRUTH_ORIF_EXPR 130 
#define  TRUTH_OR_EXPR 129 
#define  TRUTH_XOR_EXPR 128 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int UNORDERED_EXPR ; 
 int /*<<< orphan*/  VOID_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build3 (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  constant_boolean_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_trapping_math ; 
 int /*<<< orphan*/  integer_onep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_zerop (int /*<<< orphan*/ ) ; 
 int invert_tree_comparison (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invert_truthvalue (int /*<<< orphan*/ ) ; 
 scalar_t__ tcc_comparison ; 

tree
fold_truth_not_expr (tree arg)
{
  tree type = TREE_TYPE (arg);
  enum tree_code code = TREE_CODE (arg);

  /* If this is a comparison, we can simply invert it, except for
     floating-point non-equality comparisons, in which case we just
     enclose a TRUTH_NOT_EXPR around what we have.  */

  if (TREE_CODE_CLASS (code) == tcc_comparison)
    {
      tree op_type = TREE_TYPE (TREE_OPERAND (arg, 0));
      if (FLOAT_TYPE_P (op_type)
	  && flag_trapping_math
	  && code != ORDERED_EXPR && code != UNORDERED_EXPR
	  && code != NE_EXPR && code != EQ_EXPR)
	return NULL_TREE;
      else
	{
	  code = invert_tree_comparison (code,
					 HONOR_NANS (TYPE_MODE (op_type)));
	  if (code == ERROR_MARK)
	    return NULL_TREE;
	  else
	    return build2 (code, type,
			   TREE_OPERAND (arg, 0), TREE_OPERAND (arg, 1));
	}
    }

  switch (code)
    {
    case INTEGER_CST:
      return constant_boolean_node (integer_zerop (arg), type);

    case TRUTH_AND_EXPR:
      return build2 (TRUTH_OR_EXPR, type,
		     invert_truthvalue (TREE_OPERAND (arg, 0)),
		     invert_truthvalue (TREE_OPERAND (arg, 1)));

    case TRUTH_OR_EXPR:
      return build2 (TRUTH_AND_EXPR, type,
		     invert_truthvalue (TREE_OPERAND (arg, 0)),
		     invert_truthvalue (TREE_OPERAND (arg, 1)));

    case TRUTH_XOR_EXPR:
      /* Here we can invert either operand.  We invert the first operand
	 unless the second operand is a TRUTH_NOT_EXPR in which case our
	 result is the XOR of the first operand with the inside of the
	 negation of the second operand.  */

      if (TREE_CODE (TREE_OPERAND (arg, 1)) == TRUTH_NOT_EXPR)
	return build2 (TRUTH_XOR_EXPR, type, TREE_OPERAND (arg, 0),
		       TREE_OPERAND (TREE_OPERAND (arg, 1), 0));
      else
	return build2 (TRUTH_XOR_EXPR, type,
		       invert_truthvalue (TREE_OPERAND (arg, 0)),
		       TREE_OPERAND (arg, 1));

    case TRUTH_ANDIF_EXPR:
      return build2 (TRUTH_ORIF_EXPR, type,
		     invert_truthvalue (TREE_OPERAND (arg, 0)),
		     invert_truthvalue (TREE_OPERAND (arg, 1)));

    case TRUTH_ORIF_EXPR:
      return build2 (TRUTH_ANDIF_EXPR, type,
		     invert_truthvalue (TREE_OPERAND (arg, 0)),
		     invert_truthvalue (TREE_OPERAND (arg, 1)));

    case TRUTH_NOT_EXPR:
      return TREE_OPERAND (arg, 0);

    case COND_EXPR:
      {
	tree arg1 = TREE_OPERAND (arg, 1);
	tree arg2 = TREE_OPERAND (arg, 2);
	/* A COND_EXPR may have a throw as one operand, which
	   then has void type.  Just leave void operands
	   as they are.  */
	return build3 (COND_EXPR, type, TREE_OPERAND (arg, 0),
		       VOID_TYPE_P (TREE_TYPE (arg1))
		       ? arg1 : invert_truthvalue (arg1),
		       VOID_TYPE_P (TREE_TYPE (arg2))
		       ? arg2 : invert_truthvalue (arg2));
      }

    case COMPOUND_EXPR:
      return build2 (COMPOUND_EXPR, type, TREE_OPERAND (arg, 0),
		     invert_truthvalue (TREE_OPERAND (arg, 1)));

    case NON_LVALUE_EXPR:
      return invert_truthvalue (TREE_OPERAND (arg, 0));

    case NOP_EXPR:
      if (TREE_CODE (TREE_TYPE (arg)) == BOOLEAN_TYPE)
	return build1 (TRUTH_NOT_EXPR, type, arg);

    case CONVERT_EXPR:
    case FLOAT_EXPR:
      return build1 (TREE_CODE (arg), type,
		     invert_truthvalue (TREE_OPERAND (arg, 0)));

    case BIT_AND_EXPR:
      if (!integer_onep (TREE_OPERAND (arg, 1)))
	break;
      return build2 (EQ_EXPR, type, arg,
		     build_int_cst (type, 0));

    case SAVE_EXPR:
      return build1 (TRUTH_NOT_EXPR, type, arg);

    case CLEANUP_POINT_EXPR:
      return build1 (CLEANUP_POINT_EXPR, type,
		     invert_truthvalue (TREE_OPERAND (arg, 0)));

    default:
      break;
    }

  return NULL_TREE;
}