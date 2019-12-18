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
 int /*<<< orphan*/  CHREC_LEFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHREC_RIGHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHREC_VARIABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ CONVERT_EXPR ; 
 int /*<<< orphan*/  INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ NOP_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ POLYNOMIAL_CHREC ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_polynomial_chrec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_used_pointer_cast (tree expr)
{
  tree op;
  tree type, inner_type;

  if (TREE_CODE (expr) != NOP_EXPR && TREE_CODE (expr) != CONVERT_EXPR)
    return expr;

  op = TREE_OPERAND (expr, 0);
  if (TREE_CODE (op) != POLYNOMIAL_CHREC)
    return expr;

  type = TREE_TYPE (expr);
  inner_type = TREE_TYPE (op);

  if (!INTEGRAL_TYPE_P (inner_type)
      || TYPE_PRECISION (inner_type) != TYPE_PRECISION (type))
    return expr;

  return build_polynomial_chrec (CHREC_VARIABLE (op),
		chrec_convert (type, CHREC_LEFT (op), NULL_TREE),
		chrec_convert (type, CHREC_RIGHT (op), NULL_TREE));
}