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
 int ABS_EXPR ; 
 scalar_t__ COMPARISON_CLASS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ COND_EXPR ; 
 int /*<<< orphan*/  COND_EXPR_COND (int /*<<< orphan*/ ) ; 
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MODIFY_EXPR ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int TRUNC_DIV_EXPR ; 
 int TRUNC_MOD_EXPR ; 
 scalar_t__ integer_pow2p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_abs_using_ranges (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_cond_using_ranges (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_div_or_mod_using_ranges (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
simplify_stmt_using_ranges (tree stmt)
{
  if (TREE_CODE (stmt) == MODIFY_EXPR)
    {
      tree rhs = TREE_OPERAND (stmt, 1);
      enum tree_code rhs_code = TREE_CODE (rhs);

      /* Transform TRUNC_DIV_EXPR and TRUNC_MOD_EXPR into RSHIFT_EXPR
	 and BIT_AND_EXPR respectively if the first operand is greater
	 than zero and the second operand is an exact power of two.  */
      if ((rhs_code == TRUNC_DIV_EXPR || rhs_code == TRUNC_MOD_EXPR)
	  && INTEGRAL_TYPE_P (TREE_TYPE (TREE_OPERAND (rhs, 0)))
	  && integer_pow2p (TREE_OPERAND (rhs, 1)))
	simplify_div_or_mod_using_ranges (stmt, rhs, rhs_code);

      /* Transform ABS (X) into X or -X as appropriate.  */
      if (rhs_code == ABS_EXPR
	  && TREE_CODE (TREE_OPERAND (rhs, 0)) == SSA_NAME
	  && INTEGRAL_TYPE_P (TREE_TYPE (TREE_OPERAND (rhs, 0))))
	simplify_abs_using_ranges (stmt, rhs);
    }
  else if (TREE_CODE (stmt) == COND_EXPR
	   && COMPARISON_CLASS_P (COND_EXPR_COND (stmt)))
    {
      simplify_cond_using_ranges (stmt);
    }
}