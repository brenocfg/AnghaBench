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
typedef  enum built_in_function { ____Placeholder_built_in_function } built_in_function ;
struct TYPE_3__ {scalar_t__ (* global_bindings_p ) () ;} ;
struct TYPE_4__ {TYPE_1__ decls; } ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 scalar_t__ BUILTIN_SQRT_P (int) ; 
 scalar_t__ CONTAINS_PLACEHOLDER_P (int /*<<< orphan*/ ) ; 
 int EQ_EXPR ; 
 int GE_EXPR ; 
 int GT_EXPR ; 
 scalar_t__ HONOR_INFINITIES (int) ; 
 int /*<<< orphan*/  HONOR_NANS (int) ; 
 int LE_EXPR ; 
 int LT_EXPR ; 
 int /*<<< orphan*/  MULT_EXPR ; 
 int NE_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  REAL_ARITHMETIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ REAL_VALUE_ISINF (int /*<<< orphan*/ ) ; 
 scalar_t__ REAL_VALUE_NEGATIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_REAL_CST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int TRUTH_ANDIF_EXPR ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dconst0 ; 
 int /*<<< orphan*/  fold_build2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  omit_one_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  real_convert (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_expr (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 () ; 
 scalar_t__ stub2 () ; 

__attribute__((used)) static tree
fold_mathfn_compare (enum built_in_function fcode, enum tree_code code,
		     tree type, tree arg0, tree arg1)
{
  REAL_VALUE_TYPE c;

  if (BUILTIN_SQRT_P (fcode))
    {
      tree arg = TREE_VALUE (TREE_OPERAND (arg0, 1));
      enum machine_mode mode = TYPE_MODE (TREE_TYPE (arg0));

      c = TREE_REAL_CST (arg1);
      if (REAL_VALUE_NEGATIVE (c))
	{
	  /* sqrt(x) < y is always false, if y is negative.  */
	  if (code == EQ_EXPR || code == LT_EXPR || code == LE_EXPR)
	    return omit_one_operand (type, integer_zero_node, arg);

	  /* sqrt(x) > y is always true, if y is negative and we
	     don't care about NaNs, i.e. negative values of x.  */
	  if (code == NE_EXPR || !HONOR_NANS (mode))
	    return omit_one_operand (type, integer_one_node, arg);

	  /* sqrt(x) > y is the same as x >= 0, if y is negative.  */
	  return fold_build2 (GE_EXPR, type, arg,
			      build_real (TREE_TYPE (arg), dconst0));
	}
      else if (code == GT_EXPR || code == GE_EXPR)
	{
	  REAL_VALUE_TYPE c2;

	  REAL_ARITHMETIC (c2, MULT_EXPR, c, c);
	  real_convert (&c2, mode, &c2);

	  if (REAL_VALUE_ISINF (c2))
	    {
	      /* sqrt(x) > y is x == +Inf, when y is very large.  */
	      if (HONOR_INFINITIES (mode))
		return fold_build2 (EQ_EXPR, type, arg,
				    build_real (TREE_TYPE (arg), c2));

	      /* sqrt(x) > y is always false, when y is very large
		 and we don't care about infinities.  */
	      return omit_one_operand (type, integer_zero_node, arg);
	    }

	  /* sqrt(x) > c is the same as x > c*c.  */
	  return fold_build2 (code, type, arg,
			      build_real (TREE_TYPE (arg), c2));
	}
      else if (code == LT_EXPR || code == LE_EXPR)
	{
	  REAL_VALUE_TYPE c2;

	  REAL_ARITHMETIC (c2, MULT_EXPR, c, c);
	  real_convert (&c2, mode, &c2);

	  if (REAL_VALUE_ISINF (c2))
	    {
	      /* sqrt(x) < y is always true, when y is a very large
		 value and we don't care about NaNs or Infinities.  */
	      if (! HONOR_NANS (mode) && ! HONOR_INFINITIES (mode))
		return omit_one_operand (type, integer_one_node, arg);

	      /* sqrt(x) < y is x != +Inf when y is very large and we
		 don't care about NaNs.  */
	      if (! HONOR_NANS (mode))
		return fold_build2 (NE_EXPR, type, arg,
				    build_real (TREE_TYPE (arg), c2));

	      /* sqrt(x) < y is x >= 0 when y is very large and we
		 don't care about Infinities.  */
	      if (! HONOR_INFINITIES (mode))
		return fold_build2 (GE_EXPR, type, arg,
				    build_real (TREE_TYPE (arg), dconst0));

	      /* sqrt(x) < y is x >= 0 && x != +Inf, when y is large.  */
	      if (lang_hooks.decls.global_bindings_p () != 0
		  || CONTAINS_PLACEHOLDER_P (arg))
		return NULL_TREE;

	      arg = save_expr (arg);
	      return fold_build2 (TRUTH_ANDIF_EXPR, type,
				  fold_build2 (GE_EXPR, type, arg,
					       build_real (TREE_TYPE (arg),
							   dconst0)),
				  fold_build2 (NE_EXPR, type, arg,
					       build_real (TREE_TYPE (arg),
							   c2)));
	    }

	  /* sqrt(x) < c is the same as x < c*c, if we ignore NaNs.  */
	  if (! HONOR_NANS (mode))
	    return fold_build2 (code, type, arg,
				build_real (TREE_TYPE (arg), c2));

	  /* sqrt(x) < c is the same as x >= 0 && x < c*c.  */
	  if (lang_hooks.decls.global_bindings_p () == 0
	      && ! CONTAINS_PLACEHOLDER_P (arg))
	    {
	      arg = save_expr (arg);
	      return fold_build2 (TRUTH_ANDIF_EXPR, type,
				  fold_build2 (GE_EXPR, type, arg,
					       build_real (TREE_TYPE (arg),
							   dconst0)),
				  fold_build2 (code, type, arg,
					       build_real (TREE_TYPE (arg),
							   c2)));
	    }
	}
    }

  return NULL_TREE;
}