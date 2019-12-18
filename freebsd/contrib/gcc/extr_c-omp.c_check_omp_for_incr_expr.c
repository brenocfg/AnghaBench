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
 int /*<<< orphan*/  INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
#define  MINUS_EXPR 130 
#define  NOP_EXPR 129 
#define  PLUS_EXPR 128 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 scalar_t__ build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ fold_build2 (int const,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static tree
check_omp_for_incr_expr (tree exp, tree decl)
{
  tree t;

  if (!INTEGRAL_TYPE_P (TREE_TYPE (exp))
      || TYPE_PRECISION (TREE_TYPE (exp)) < TYPE_PRECISION (TREE_TYPE (decl)))
    return error_mark_node;

  if (exp == decl)
    return build_int_cst (TREE_TYPE (exp), 0);

  switch (TREE_CODE (exp))
    {
    case NOP_EXPR:
      t = check_omp_for_incr_expr (TREE_OPERAND (exp, 0), decl);
      if (t != error_mark_node)
        return fold_convert (TREE_TYPE (exp), t);
      break;
    case MINUS_EXPR:
      t = check_omp_for_incr_expr (TREE_OPERAND (exp, 0), decl);
      if (t != error_mark_node)
        return fold_build2 (MINUS_EXPR, TREE_TYPE (exp), t, TREE_OPERAND (exp, 1));
      break;
    case PLUS_EXPR:
      t = check_omp_for_incr_expr (TREE_OPERAND (exp, 0), decl);
      if (t != error_mark_node)
        return fold_build2 (PLUS_EXPR, TREE_TYPE (exp), t, TREE_OPERAND (exp, 1));
      t = check_omp_for_incr_expr (TREE_OPERAND (exp, 1), decl);
      if (t != error_mark_node)
        return fold_build2 (PLUS_EXPR, TREE_TYPE (exp), TREE_OPERAND (exp, 0), t);
      break;
    default:
      break;
    }

  return error_mark_node;
}