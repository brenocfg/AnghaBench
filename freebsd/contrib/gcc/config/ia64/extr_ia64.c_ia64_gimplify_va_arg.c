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
 int BITS_PER_UNIT ; 
 int /*<<< orphan*/  BIT_AND_EXPR ; 
 scalar_t__ INTEGER_TYPE ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ REAL_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int TYPE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int UNITS_PER_WORD ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_va_arg_indirect_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimplify_and_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int int_size_in_bytes (int /*<<< orphan*/ ) ; 
 scalar_t__ pass_by_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  std_gimplify_va_arg_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
ia64_gimplify_va_arg (tree valist, tree type, tree *pre_p, tree *post_p)
{
  /* Variable sized types are passed by reference.  */
  if (pass_by_reference (NULL, TYPE_MODE (type), type, false))
    {
      tree ptrtype = build_pointer_type (type);
      tree addr = std_gimplify_va_arg_expr (valist, ptrtype, pre_p, post_p);
      return build_va_arg_indirect_ref (addr);
    }

  /* Aggregate arguments with alignment larger than 8 bytes start at
     the next even boundary.  Integer and floating point arguments
     do so if they are larger than 8 bytes, whether or not they are
     also aligned larger than 8 bytes.  */
  if ((TREE_CODE (type) == REAL_TYPE || TREE_CODE (type) == INTEGER_TYPE)
      ? int_size_in_bytes (type) > 8 : TYPE_ALIGN (type) > 8 * BITS_PER_UNIT)
    {
      tree t = build2 (PLUS_EXPR, TREE_TYPE (valist), valist,
		       build_int_cst (NULL_TREE, 2 * UNITS_PER_WORD - 1));
      t = build2 (BIT_AND_EXPR, TREE_TYPE (t), t,
		  build_int_cst (NULL_TREE, -2 * UNITS_PER_WORD));
      t = build2 (MODIFY_EXPR, TREE_TYPE (valist), valist, t);
      gimplify_and_add (t, pre_p);
    }

  return std_gimplify_va_arg_expr (valist, type, pre_p, post_p);
}