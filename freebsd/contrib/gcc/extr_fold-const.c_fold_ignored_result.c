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
#define  COMPOUND_EXPR 133 
#define  COND_EXPR 132 
 int /*<<< orphan*/  TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_CODE_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TREE_SIDE_EFFECTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_zero_node ; 
#define  tcc_binary 131 
#define  tcc_comparison 130 
#define  tcc_expression 129 
#define  tcc_unary 128 

tree
fold_ignored_result (tree t)
{
  if (!TREE_SIDE_EFFECTS (t))
    return integer_zero_node;

  for (;;)
    switch (TREE_CODE_CLASS (TREE_CODE (t)))
      {
      case tcc_unary:
	t = TREE_OPERAND (t, 0);
	break;

      case tcc_binary:
      case tcc_comparison:
	if (!TREE_SIDE_EFFECTS (TREE_OPERAND (t, 1)))
	  t = TREE_OPERAND (t, 0);
	else if (!TREE_SIDE_EFFECTS (TREE_OPERAND (t, 0)))
	  t = TREE_OPERAND (t, 1);
	else
	  return t;
	break;

      case tcc_expression:
	switch (TREE_CODE (t))
	  {
	  case COMPOUND_EXPR:
	    if (TREE_SIDE_EFFECTS (TREE_OPERAND (t, 1)))
	      return t;
	    t = TREE_OPERAND (t, 0);
	    break;

	  case COND_EXPR:
	    if (TREE_SIDE_EFFECTS (TREE_OPERAND (t, 1))
		|| TREE_SIDE_EFFECTS (TREE_OPERAND (t, 2)))
	      return t;
	    t = TREE_OPERAND (t, 0);
	    break;

	  default:
	    return t;
	  }
	break;

      default:
	return t;
      }
}