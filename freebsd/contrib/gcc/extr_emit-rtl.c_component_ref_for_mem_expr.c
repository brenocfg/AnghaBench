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
 scalar_t__ COMPONENT_REF ; 
 scalar_t__ CONVERT_EXPR ; 
 int /*<<< orphan*/  DECL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ NON_LVALUE_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ SAVE_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VIEW_CONVERT_EXPR ; 
 int /*<<< orphan*/  build3 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
component_ref_for_mem_expr (tree ref)
{
  tree inner = TREE_OPERAND (ref, 0);

  if (TREE_CODE (inner) == COMPONENT_REF)
    inner = component_ref_for_mem_expr (inner);
  else
    {
      /* Now remove any conversions: they don't change what the underlying
	 object is.  Likewise for SAVE_EXPR.  */
      while (TREE_CODE (inner) == NOP_EXPR || TREE_CODE (inner) == CONVERT_EXPR
	     || TREE_CODE (inner) == NON_LVALUE_EXPR
	     || TREE_CODE (inner) == VIEW_CONVERT_EXPR
	     || TREE_CODE (inner) == SAVE_EXPR)
	inner = TREE_OPERAND (inner, 0);

      if (! DECL_P (inner))
	inner = NULL_TREE;
    }

  if (inner == TREE_OPERAND (ref, 0))
    return ref;
  else
    return build3 (COMPONENT_REF, TREE_TYPE (ref), inner,
		   TREE_OPERAND (ref, 1), NULL_TREE);
}