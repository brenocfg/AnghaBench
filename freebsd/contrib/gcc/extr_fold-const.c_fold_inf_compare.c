#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_3__ {int /*<<< orphan*/  (* global_bindings_p ) () ;} ;
struct TYPE_4__ {TYPE_1__ decls; } ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  CONTAINS_PLACEHOLDER_P (int /*<<< orphan*/ ) ; 
#define  EQ_EXPR 133 
#define  GE_EXPR 132 
#define  GT_EXPR 131 
 int /*<<< orphan*/  HONOR_NANS (int) ; 
 int /*<<< orphan*/  HONOR_SNANS (int) ; 
#define  LE_EXPR 130 
#define  LT_EXPR 129 
#define  NE_EXPR 128 
 int /*<<< orphan*/  NULL_TREE ; 
 int REAL_VALUE_NEGATIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_REAL_CST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUTH_NOT_EXPR ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_gimple_form ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  omit_one_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  real_maxval (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  save_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int swap_tree_comparison (int) ; 

__attribute__((used)) static tree
fold_inf_compare (enum tree_code code, tree type, tree arg0, tree arg1)
{
  enum machine_mode mode;
  REAL_VALUE_TYPE max;
  tree temp;
  bool neg;

  mode = TYPE_MODE (TREE_TYPE (arg0));

  /* For negative infinity swap the sense of the comparison.  */
  neg = REAL_VALUE_NEGATIVE (TREE_REAL_CST (arg1));
  if (neg)
    code = swap_tree_comparison (code);

  switch (code)
    {
    case GT_EXPR:
      /* x > +Inf is always false, if with ignore sNANs.  */
      if (HONOR_SNANS (mode))
        return NULL_TREE;
      return omit_one_operand (type, integer_zero_node, arg0);

    case LE_EXPR:
      /* x <= +Inf is always true, if we don't case about NaNs.  */
      if (! HONOR_NANS (mode))
	return omit_one_operand (type, integer_one_node, arg0);

      /* x <= +Inf is the same as x == x, i.e. isfinite(x).  */
      if (lang_hooks.decls.global_bindings_p () == 0
	  && ! CONTAINS_PLACEHOLDER_P (arg0))
	{
	  arg0 = save_expr (arg0);
	  return fold_build2 (EQ_EXPR, type, arg0, arg0);
	}
      break;

    case EQ_EXPR:
    case GE_EXPR:
      /* x == +Inf and x >= +Inf are always equal to x > DBL_MAX.  */
      real_maxval (&max, neg, mode);
      return fold_build2 (neg ? LT_EXPR : GT_EXPR, type,
			  arg0, build_real (TREE_TYPE (arg0), max));

    case LT_EXPR:
      /* x < +Inf is always equal to x <= DBL_MAX.  */
      real_maxval (&max, neg, mode);
      return fold_build2 (neg ? GE_EXPR : LE_EXPR, type,
			  arg0, build_real (TREE_TYPE (arg0), max));

    case NE_EXPR:
      /* x != +Inf is always equal to !(x > DBL_MAX).  */
      real_maxval (&max, neg, mode);
      if (! HONOR_NANS (mode))
	return fold_build2 (neg ? GE_EXPR : LE_EXPR, type,
			    arg0, build_real (TREE_TYPE (arg0), max));

      /* The transformation below creates non-gimple code and thus is
	 not appropriate if we are in gimple form.  */
      if (in_gimple_form)
	return NULL_TREE;

      temp = fold_build2 (neg ? LT_EXPR : GT_EXPR, type,
			  arg0, build_real (TREE_TYPE (arg0), max));
      return fold_build1 (TRUTH_NOT_EXPR, type, temp);

    default:
      break;
    }

  return NULL_TREE;
}