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
 int /*<<< orphan*/  CONSTANT_CLASS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CONST_DECL ; 
 scalar_t__ EXC_PTR_EXPR ; 
 scalar_t__ FILTER_EXPR ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ LABEL_DECL ; 
 int /*<<< orphan*/  SSA_VAR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
get_base_var (tree t)
{
  if ((TREE_CODE (t) == EXC_PTR_EXPR) || (TREE_CODE (t) == FILTER_EXPR))
    return t;

  while (!SSA_VAR_P (t) 
	 && (!CONSTANT_CLASS_P (t))
	 && TREE_CODE (t) != LABEL_DECL
	 && TREE_CODE (t) != FUNCTION_DECL
	 && TREE_CODE (t) != CONST_DECL)
    {
      t = TREE_OPERAND (t, 0);
    }
  return t;
}