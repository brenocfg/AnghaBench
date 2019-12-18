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
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_CLASS_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_POINTED_TO_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PTR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PTR_TO_MEMBER_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_nop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ comp_ptr_ttypes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_mark_node ; 
 scalar_t__ same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
perform_qualification_conversions (tree type, tree expr)
{
  tree expr_type;

  expr_type = TREE_TYPE (expr);

  if (same_type_p (type, expr_type))
    return expr;
  else if (TYPE_PTR_P (type) && TYPE_PTR_P (expr_type)
	   && comp_ptr_ttypes (TREE_TYPE (type), TREE_TYPE (expr_type)))
    return build_nop (type, expr);
  else if (TYPE_PTR_TO_MEMBER_P (type)
	   && TYPE_PTR_TO_MEMBER_P (expr_type)
	   && same_type_p (TYPE_PTRMEM_CLASS_TYPE (type),
			   TYPE_PTRMEM_CLASS_TYPE (expr_type))
	   && comp_ptr_ttypes (TYPE_PTRMEM_POINTED_TO_TYPE (type),
			       TYPE_PTRMEM_POINTED_TO_TYPE (expr_type)))
    return build_nop (type, expr);
  else
    return error_mark_node;
}