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
 scalar_t__ ARRAY_RANGE_REF ; 
 scalar_t__ ARRAY_REF ; 
 scalar_t__ CASE_LABEL_EXPR ; 
 scalar_t__ COMPONENT_REF ; 
 scalar_t__ DECL_P (scalar_t__) ; 
 scalar_t__ IDENTIFIER_NODE ; 
 scalar_t__ IMAGPART_EXPR ; 
 scalar_t__ IS_TYPE_OR_DECL_P (scalar_t__) ; 
 scalar_t__ REALPART_EXPR ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ is_gimple_min_invariant (scalar_t__) ; 

__attribute__((used)) static bool
tree_node_can_be_shared (tree t)
{
  if (IS_TYPE_OR_DECL_P (t)
      || is_gimple_min_invariant (t)
      || TREE_CODE (t) == SSA_NAME
      || t == error_mark_node
      || TREE_CODE (t) == IDENTIFIER_NODE)
    return true;

  if (TREE_CODE (t) == CASE_LABEL_EXPR)
    return true;

  while (((TREE_CODE (t) == ARRAY_REF || TREE_CODE (t) == ARRAY_RANGE_REF)
	   && is_gimple_min_invariant (TREE_OPERAND (t, 1)))
	 || TREE_CODE (t) == COMPONENT_REF
	 || TREE_CODE (t) == REALPART_EXPR
	 || TREE_CODE (t) == IMAGPART_EXPR)
    t = TREE_OPERAND (t, 0);

  if (DECL_P (t))
    return true;

  return false;
}