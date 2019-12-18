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
 int /*<<< orphan*/  COMPLETE_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXACT_DIV_EXPR ; 
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ METHOD_TYPE ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PTROB_P (int /*<<< orphan*/ ) ; 
 scalar_t__ VOID_TYPE ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_type_or_else (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_build_binary_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  fold_if_not_in_template (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_one_node ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 int /*<<< orphan*/  ptrdiff_type_node ; 
 int /*<<< orphan*/  size_in_bytes (int /*<<< orphan*/ ) ; 
 scalar_t__ warn_pointer_arith ; 

__attribute__((used)) static tree
pointer_diff (tree op0, tree op1, tree ptrtype)
{
  tree result;
  tree restype = ptrdiff_type_node;
  tree target_type = TREE_TYPE (ptrtype);

  if (!complete_type_or_else (target_type, NULL_TREE))
    return error_mark_node;

  if (pedantic || warn_pointer_arith)
    {
      if (TREE_CODE (target_type) == VOID_TYPE)
	pedwarn ("ISO C++ forbids using pointer of type %<void *%> in subtraction");
      if (TREE_CODE (target_type) == FUNCTION_TYPE)
	pedwarn ("ISO C++ forbids using pointer to a function in subtraction");
      if (TREE_CODE (target_type) == METHOD_TYPE)
	pedwarn ("ISO C++ forbids using pointer to a method in subtraction");
    }

  /* First do the subtraction as integers;
     then drop through to build the divide operator.  */

  op0 = cp_build_binary_op (MINUS_EXPR,
			    cp_convert (restype, op0),
			    cp_convert (restype, op1));

  /* This generates an error if op1 is a pointer to an incomplete type.  */
  if (!COMPLETE_TYPE_P (TREE_TYPE (TREE_TYPE (op1))))
    error ("invalid use of a pointer to an incomplete type in pointer arithmetic");

  op1 = (TYPE_PTROB_P (ptrtype)
	 ? size_in_bytes (target_type)
	 : integer_one_node);

  /* Do the division.  */

  result = build2 (EXACT_DIV_EXPR, restype, op0, cp_convert (restype, op1));
  return fold_if_not_in_template (result);
}