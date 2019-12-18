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
 scalar_t__ ARRAY_REF ; 
 scalar_t__ EXC_PTR_EXPR ; 
 scalar_t__ FILTER_EXPR ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ IMAGPART_EXPR ; 
 scalar_t__ INDIRECT_REF_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REALPART_EXPR ; 
 scalar_t__ SSA_VAR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_operand (int /*<<< orphan*/ ) ; 
 scalar_t__ handled_component_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_tree (tree t)
{
  if ((TREE_CODE (t) == EXC_PTR_EXPR) || (TREE_CODE (t) == FILTER_EXPR))
    return;

  while (TREE_CODE (t) == REALPART_EXPR 
	 || TREE_CODE (t) == IMAGPART_EXPR
	 || handled_component_p (t))
    {
      if (TREE_CODE (t) == ARRAY_REF)
	check_operand (TREE_OPERAND (t, 1));
      t = TREE_OPERAND (t, 0);
    }

  if (INDIRECT_REF_P (t))
/*  || TREE_CODE (t) == MEM_REF) */
    check_tree (TREE_OPERAND (t, 0));

  if (SSA_VAR_P (t) || (TREE_CODE (t) == FUNCTION_DECL))
    check_operand (t);
}