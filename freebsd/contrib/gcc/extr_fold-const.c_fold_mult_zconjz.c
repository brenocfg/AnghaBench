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
 scalar_t__ COMPLEX_CST ; 
 scalar_t__ COMPLEX_EXPR ; 
 int /*<<< orphan*/  IMAGPART_EXPR ; 
 scalar_t__ MULT_EXPR ; 
 scalar_t__ PLUS_EXPR ; 
 int /*<<< orphan*/  REALPART_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_IMAGPART (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_REALPART (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  save_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_mult_zconjz (tree type, tree expr)
{
  tree itype = TREE_TYPE (type);
  tree rpart, ipart, tem;

  if (TREE_CODE (expr) == COMPLEX_EXPR)
    {
      rpart = TREE_OPERAND (expr, 0);
      ipart = TREE_OPERAND (expr, 1);
    }
  else if (TREE_CODE (expr) == COMPLEX_CST)
    {
      rpart = TREE_REALPART (expr);
      ipart = TREE_IMAGPART (expr);
    }
  else
    {
      expr = save_expr (expr);
      rpart = fold_build1 (REALPART_EXPR, itype, expr);
      ipart = fold_build1 (IMAGPART_EXPR, itype, expr);
    }

  rpart = save_expr (rpart);
  ipart = save_expr (ipart);
  tem = fold_build2 (PLUS_EXPR, itype,
		     fold_build2 (MULT_EXPR, itype, rpart, rpart),
		     fold_build2 (MULT_EXPR, itype, ipart, ipart));
  return fold_build2 (COMPLEX_EXPR, type, tem,
		      fold_convert (itype, integer_zero_node));
}