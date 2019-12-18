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
struct loop {int dummy; } ;

/* Variables and functions */
#define  ASSERT_EXPR 135 
 int /*<<< orphan*/  ASSERT_EXPR_VAR (int /*<<< orphan*/ ) ; 
#define  CONVERT_EXPR 134 
#define  MINUS_EXPR 133 
#define  MULT_EXPR 132 
#define  NEGATE_EXPR 131 
#define  NOP_EXPR 130 
#define  PLUS_EXPR 129 
#define  SSA_NAME 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  analyze_scalar_evolution (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_dont_know ; 
 int /*<<< orphan*/  chrec_fold_minus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_fold_multiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_fold_plus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_minus_one_node ; 
 scalar_t__ is_gimple_min_invariant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
interpret_rhs_modify_expr (struct loop *loop, tree at_stmt,
			   tree opnd1, tree type)
{
  tree res, opnd10, opnd11, chrec10, chrec11;

  if (is_gimple_min_invariant (opnd1))
    return chrec_convert (type, opnd1, at_stmt);

  switch (TREE_CODE (opnd1))
    {
    case PLUS_EXPR:
      opnd10 = TREE_OPERAND (opnd1, 0);
      opnd11 = TREE_OPERAND (opnd1, 1);
      chrec10 = analyze_scalar_evolution (loop, opnd10);
      chrec11 = analyze_scalar_evolution (loop, opnd11);
      chrec10 = chrec_convert (type, chrec10, at_stmt);
      chrec11 = chrec_convert (type, chrec11, at_stmt);
      res = chrec_fold_plus (type, chrec10, chrec11);
      break;
      
    case MINUS_EXPR:
      opnd10 = TREE_OPERAND (opnd1, 0);
      opnd11 = TREE_OPERAND (opnd1, 1);
      chrec10 = analyze_scalar_evolution (loop, opnd10);
      chrec11 = analyze_scalar_evolution (loop, opnd11);
      chrec10 = chrec_convert (type, chrec10, at_stmt);
      chrec11 = chrec_convert (type, chrec11, at_stmt);
      res = chrec_fold_minus (type, chrec10, chrec11);
      break;

    case NEGATE_EXPR:
      opnd10 = TREE_OPERAND (opnd1, 0);
      chrec10 = analyze_scalar_evolution (loop, opnd10);
      chrec10 = chrec_convert (type, chrec10, at_stmt);
      /* TYPE may be integer, real or complex, so use fold_convert.  */
      res = chrec_fold_multiply (type, chrec10,
				 fold_convert (type, integer_minus_one_node));
      break;

    case MULT_EXPR:
      opnd10 = TREE_OPERAND (opnd1, 0);
      opnd11 = TREE_OPERAND (opnd1, 1);
      chrec10 = analyze_scalar_evolution (loop, opnd10);
      chrec11 = analyze_scalar_evolution (loop, opnd11);
      chrec10 = chrec_convert (type, chrec10, at_stmt);
      chrec11 = chrec_convert (type, chrec11, at_stmt);
      res = chrec_fold_multiply (type, chrec10, chrec11);
      break;
      
    case SSA_NAME:
      res = chrec_convert (type, analyze_scalar_evolution (loop, opnd1),
			   at_stmt);
      break;

    case ASSERT_EXPR:
      opnd10 = ASSERT_EXPR_VAR (opnd1);
      res = chrec_convert (type, analyze_scalar_evolution (loop, opnd10),
			   at_stmt);
      break;
      
    case NOP_EXPR:
    case CONVERT_EXPR:
      opnd10 = TREE_OPERAND (opnd1, 0);
      chrec10 = analyze_scalar_evolution (loop, opnd10);
      res = chrec_convert (type, chrec10, at_stmt);
      break;
      
    default:
      res = chrec_dont_know;
      break;
    }
  
  return res;
}