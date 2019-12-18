#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ type; } ;
typedef  TYPE_1__ value_range_t ;
typedef  int /*<<< orphan*/  tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int ASSERT_EXPR ; 
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 int SSA_NAME ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE_CLASS (int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int TRUTH_ANDIF_EXPR ; 
 int TRUTH_AND_EXPR ; 
 int TRUTH_ORIF_EXPR ; 
 int TRUTH_OR_EXPR ; 
 int TRUTH_XOR_EXPR ; 
 scalar_t__ VR_VARYING ; 
 int /*<<< orphan*/  extract_range_from_assert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_range_from_binary_expr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_range_from_comparison (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_range_from_ssa_name (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_range_from_unary_expr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_gimple_min_invariant (int /*<<< orphan*/ ) ; 
 scalar_t__ is_overflow_infinity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_value_range_to_nonnegative (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_value_range_to_nonnull (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_value_range_to_value (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_value_range_to_varying (TYPE_1__*) ; 
 scalar_t__ tcc_binary ; 
 scalar_t__ tcc_comparison ; 
 scalar_t__ tcc_unary ; 
 scalar_t__ vrp_expr_computes_nonnegative (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ vrp_expr_computes_nonzero (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
extract_range_from_expr (value_range_t *vr, tree expr)
{
  enum tree_code code = TREE_CODE (expr);

  if (code == ASSERT_EXPR)
    extract_range_from_assert (vr, expr);
  else if (code == SSA_NAME)
    extract_range_from_ssa_name (vr, expr);
  else if (TREE_CODE_CLASS (code) == tcc_binary
	   || code == TRUTH_ANDIF_EXPR
	   || code == TRUTH_ORIF_EXPR
	   || code == TRUTH_AND_EXPR
	   || code == TRUTH_OR_EXPR
	   || code == TRUTH_XOR_EXPR)
    extract_range_from_binary_expr (vr, expr);
  else if (TREE_CODE_CLASS (code) == tcc_unary)
    extract_range_from_unary_expr (vr, expr);
  else if (TREE_CODE_CLASS (code) == tcc_comparison)
    extract_range_from_comparison (vr, expr);
  else if (is_gimple_min_invariant (expr))
    set_value_range_to_value (vr, expr, NULL);
  else
    set_value_range_to_varying (vr);

  /* If we got a varying range from the tests above, try a final
     time to derive a nonnegative or nonzero range.  This time
     relying primarily on generic routines in fold in conjunction
     with range data.  */
  if (vr->type == VR_VARYING)
    {
      bool sop = false;

      if (INTEGRAL_TYPE_P (TREE_TYPE (expr))
	  && vrp_expr_computes_nonnegative (expr, &sop))
	set_value_range_to_nonnegative (vr, TREE_TYPE (expr),
					sop || is_overflow_infinity (expr));
      else if (vrp_expr_computes_nonzero (expr, &sop)
	       && !sop)
        set_value_range_to_nonnull (vr, TREE_TYPE (expr));
    }
}