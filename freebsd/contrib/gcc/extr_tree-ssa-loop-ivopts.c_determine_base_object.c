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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
#define  ADDR_EXPR 131 
 scalar_t__ CONVERT_EXPR ; 
 scalar_t__ INDIRECT_REF ; 
#define  INTEGER_CST 130 
#define  MINUS_EXPR 129 
 int /*<<< orphan*/  NEGATE_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
#define  PLUS_EXPR 128 
 int /*<<< orphan*/  POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_fold_addr_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_base_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr_type_node ; 

__attribute__((used)) static tree
determine_base_object (tree expr)
{
  enum tree_code code = TREE_CODE (expr);
  tree base, obj, op0, op1;

  /* If this is a pointer casted to any type, we need to determine
     the base object for the pointer; so handle conversions before
     throwing away non-pointer expressions.  */
  if (TREE_CODE (expr) == NOP_EXPR
      || TREE_CODE (expr) == CONVERT_EXPR)
    return determine_base_object (TREE_OPERAND (expr, 0));

  if (!POINTER_TYPE_P (TREE_TYPE (expr)))
    return NULL_TREE;

  switch (code)
    {
    case INTEGER_CST:
      return NULL_TREE;

    case ADDR_EXPR:
      obj = TREE_OPERAND (expr, 0);
      base = get_base_address (obj);

      if (!base)
	return expr;

      if (TREE_CODE (base) == INDIRECT_REF)
	return determine_base_object (TREE_OPERAND (base, 0));

      return fold_convert (ptr_type_node,
		           build_fold_addr_expr (base));

    case PLUS_EXPR:
    case MINUS_EXPR:
      op0 = determine_base_object (TREE_OPERAND (expr, 0));
      op1 = determine_base_object (TREE_OPERAND (expr, 1));
      
      if (!op1)
	return op0;

      if (!op0)
	return (code == PLUS_EXPR
		? op1
		: fold_build1 (NEGATE_EXPR, ptr_type_node, op1));

      return fold_build2 (code, ptr_type_node, op0, op1);

    default:
      return fold_convert (ptr_type_node, expr);
    }
}