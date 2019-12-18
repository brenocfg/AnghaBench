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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
#define  ARRAY_REF 135 
 int BITS_PER_UNIT ; 
#define  COMPONENT_REF 134 
#define  CONVERT_EXPR 133 
 int /*<<< orphan*/  DECL_FIELD_BIT_OFFSET (scalar_t__) ; 
 scalar_t__ DECL_FIELD_OFFSET (scalar_t__) ; 
#define  IMAGPART_EXPR 132 
 int INTEGER_CST ; 
 int MINUS_EXPR ; 
 int MULT_EXPR ; 
 int /*<<< orphan*/  NEGATE_EXPR ; 
#define  NON_LVALUE_EXPR 131 
#define  NOP_EXPR 130 
 int PLUS_EXPR ; 
#define  REALPART_EXPR 129 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
#define  VIEW_CONVERT_EXPR 128 
 scalar_t__ error_mark_node ; 
 scalar_t__ fold_build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ fold_convert (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ size_binop (int,scalar_t__,scalar_t__) ; 
 scalar_t__ size_int (int) ; 
 scalar_t__ size_zero_node ; 
 int /*<<< orphan*/  sizetype ; 
 int /*<<< orphan*/  tree_int_cst_sgn (scalar_t__) ; 
 int tree_low_cst (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tree
compute_object_offset (tree expr, tree var)
{
  enum tree_code code = PLUS_EXPR;
  tree base, off, t;

  if (expr == var)
    return size_zero_node;

  switch (TREE_CODE (expr))
    {
    case COMPONENT_REF:
      base = compute_object_offset (TREE_OPERAND (expr, 0), var);
      if (base == error_mark_node)
	return base;

      t = TREE_OPERAND (expr, 1);
      off = size_binop (PLUS_EXPR, DECL_FIELD_OFFSET (t),
			size_int (tree_low_cst (DECL_FIELD_BIT_OFFSET (t), 1)
				  / BITS_PER_UNIT));
      break;

    case REALPART_EXPR:
    case NOP_EXPR:
    case CONVERT_EXPR:
    case VIEW_CONVERT_EXPR:
    case NON_LVALUE_EXPR:
      return compute_object_offset (TREE_OPERAND (expr, 0), var);

    case IMAGPART_EXPR:
      base = compute_object_offset (TREE_OPERAND (expr, 0), var);
      if (base == error_mark_node)
	return base;

      off = TYPE_SIZE_UNIT (TREE_TYPE (expr));
      break;

    case ARRAY_REF:
      base = compute_object_offset (TREE_OPERAND (expr, 0), var);
      if (base == error_mark_node)
	return base;

      t = TREE_OPERAND (expr, 1);
      if (TREE_CODE (t) == INTEGER_CST && tree_int_cst_sgn (t) < 0)
	{
	  code = MINUS_EXPR;
	  t = fold_build1 (NEGATE_EXPR, TREE_TYPE (t), t);
	}
      t = fold_convert (sizetype, t);
      off = size_binop (MULT_EXPR, TYPE_SIZE_UNIT (TREE_TYPE (expr)), t);
      break;

    default:
      return error_mark_node;
    }

  return size_binop (code, base, off);
}