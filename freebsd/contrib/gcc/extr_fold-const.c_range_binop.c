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

/* Variables and functions */
#define  EQ_EXPR 133 
#define  GE_EXPR 132 
#define  GT_EXPR 131 
 scalar_t__ INTEGER_CST ; 
#define  LE_EXPR 130 
#define  LT_EXPR 129 
#define  NE_EXPR 128 
 int /*<<< orphan*/  STRIP_NOPS (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_CODE_CLASS (int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ constant_boolean_node (int,scalar_t__) ; 
 scalar_t__ fold_build2 (int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ tcc_comparison ; 

__attribute__((used)) static tree
range_binop (enum tree_code code, tree type, tree arg0, int upper0_p,
	     tree arg1, int upper1_p)
{
  tree tem;
  int result;
  int sgn0, sgn1;

  /* If neither arg represents infinity, do the normal operation.
     Else, if not a comparison, return infinity.  Else handle the special
     comparison rules. Note that most of the cases below won't occur, but
     are handled for consistency.  */

  if (arg0 != 0 && arg1 != 0)
    {
      tem = fold_build2 (code, type != 0 ? type : TREE_TYPE (arg0),
			 arg0, fold_convert (TREE_TYPE (arg0), arg1));
      STRIP_NOPS (tem);
      return TREE_CODE (tem) == INTEGER_CST ? tem : 0;
    }

  if (TREE_CODE_CLASS (code) != tcc_comparison)
    return 0;

  /* Set SGN[01] to -1 if ARG[01] is a lower bound, 1 for upper, and 0
     for neither.  In real maths, we cannot assume open ended ranges are
     the same. But, this is computer arithmetic, where numbers are finite.
     We can therefore make the transformation of any unbounded range with
     the value Z, Z being greater than any representable number. This permits
     us to treat unbounded ranges as equal.  */
  sgn0 = arg0 != 0 ? 0 : (upper0_p ? 1 : -1);
  sgn1 = arg1 != 0 ? 0 : (upper1_p ? 1 : -1);
  switch (code)
    {
    case EQ_EXPR:
      result = sgn0 == sgn1;
      break;
    case NE_EXPR:
      result = sgn0 != sgn1;
      break;
    case LT_EXPR:
      result = sgn0 < sgn1;
      break;
    case LE_EXPR:
      result = sgn0 <= sgn1;
      break;
    case GT_EXPR:
      result = sgn0 > sgn1;
      break;
    case GE_EXPR:
      result = sgn0 >= sgn1;
      break;
    default:
      gcc_unreachable ();
    }

  return constant_boolean_node (result, type);
}