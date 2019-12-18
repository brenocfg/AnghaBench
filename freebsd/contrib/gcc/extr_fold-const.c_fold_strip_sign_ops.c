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
#define  ABS_EXPR 131 
 int /*<<< orphan*/  HONOR_SIGN_DEPENDENT_ROUNDING (int /*<<< orphan*/ ) ; 
#define  MULT_EXPR 130 
#define  NEGATE_EXPR 129 
 int /*<<< orphan*/  NULL_TREE ; 
#define  RDIV_EXPR 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
fold_strip_sign_ops (tree exp)
{
  tree arg0, arg1;

  switch (TREE_CODE (exp))
    {
    case ABS_EXPR:
    case NEGATE_EXPR:
      arg0 = fold_strip_sign_ops (TREE_OPERAND (exp, 0));
      return arg0 ? arg0 : TREE_OPERAND (exp, 0);

    case MULT_EXPR:
    case RDIV_EXPR:
      if (HONOR_SIGN_DEPENDENT_ROUNDING (TYPE_MODE (TREE_TYPE (exp))))
	return NULL_TREE;
      arg0 = fold_strip_sign_ops (TREE_OPERAND (exp, 0));
      arg1 = fold_strip_sign_ops (TREE_OPERAND (exp, 1));
      if (arg0 != NULL_TREE || arg1 != NULL_TREE)
	return fold_build2 (TREE_CODE (exp), TREE_TYPE (exp),
			    arg0 ? arg0 : TREE_OPERAND (exp, 0),
			    arg1 ? arg1 : TREE_OPERAND (exp, 1));
      break;

    default:
      break;
    }
  return NULL_TREE;
}