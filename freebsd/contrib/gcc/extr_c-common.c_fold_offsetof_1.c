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
#define  ARRAY_REF 136 
 int BITS_PER_UNIT ; 
#define  CALL_EXPR 135 
#define  COMPONENT_REF 134 
#define  COMPOUND_EXPR 133 
 int /*<<< orphan*/  DECL_C_BIT_FIELD (scalar_t__) ; 
 int /*<<< orphan*/  DECL_FIELD_BIT_OFFSET (scalar_t__) ; 
 scalar_t__ DECL_FIELD_OFFSET (scalar_t__) ; 
#define  ERROR_MARK 132 
#define  INDIRECT_REF 131 
#define  INTEGER_CST 130 
 int MINUS_EXPR ; 
 int MULT_EXPR ; 
 int /*<<< orphan*/  NEGATE_EXPR ; 
#define  NOP_EXPR 129 
 int PLUS_EXPR ; 
 int const TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
#define  VAR_DECL 128 
 scalar_t__ convert (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ fold_build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int integer_zerop (scalar_t__) ; 
 scalar_t__ size_binop (int,scalar_t__,scalar_t__) ; 
 scalar_t__ size_int (int) ; 
 scalar_t__ size_zero_node ; 
 int /*<<< orphan*/  sizetype ; 
 int /*<<< orphan*/  tree_int_cst_sgn (scalar_t__) ; 
 int tree_low_cst (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tree
fold_offsetof_1 (tree expr, tree stop_ref)
{
  enum tree_code code = PLUS_EXPR;
  tree base, off, t;

  if (expr == stop_ref && TREE_CODE (expr) != ERROR_MARK)
    return size_zero_node;

  switch (TREE_CODE (expr))
    {
    case ERROR_MARK:
      return expr;

    case VAR_DECL:
      error ("cannot apply %<offsetof%> to static data member %qD", expr);
      return error_mark_node;

    case CALL_EXPR:
      error ("cannot apply %<offsetof%> when %<operator[]%> is overloaded");
      return error_mark_node;

    case INTEGER_CST:
      gcc_assert (integer_zerop (expr));
      return size_zero_node;

    case NOP_EXPR:
    case INDIRECT_REF:
      base = fold_offsetof_1 (TREE_OPERAND (expr, 0), stop_ref);
      gcc_assert (base == error_mark_node || base == size_zero_node);
      return base;

    case COMPONENT_REF:
      base = fold_offsetof_1 (TREE_OPERAND (expr, 0), stop_ref);
      if (base == error_mark_node)
	return base;

      t = TREE_OPERAND (expr, 1);
      if (DECL_C_BIT_FIELD (t))
	{
	  error ("attempt to take address of bit-field structure "
		 "member %qD", t);
	  return error_mark_node;
	}
      off = size_binop (PLUS_EXPR, DECL_FIELD_OFFSET (t),
			size_int (tree_low_cst (DECL_FIELD_BIT_OFFSET (t), 1)
				  / BITS_PER_UNIT));
      break;

    case ARRAY_REF:
      base = fold_offsetof_1 (TREE_OPERAND (expr, 0), stop_ref);
      if (base == error_mark_node)
	return base;

      t = TREE_OPERAND (expr, 1);
      if (TREE_CODE (t) == INTEGER_CST && tree_int_cst_sgn (t) < 0)
	{
	  code = MINUS_EXPR;
	  t = fold_build1 (NEGATE_EXPR, TREE_TYPE (t), t);
	}
      t = convert (sizetype, t);
      off = size_binop (MULT_EXPR, TYPE_SIZE_UNIT (TREE_TYPE (expr)), t);
      break;

    case COMPOUND_EXPR:
      /* Handle static members of volatile structs.  */
      t = TREE_OPERAND (expr, 1);
      gcc_assert (TREE_CODE (t) == VAR_DECL);
      return fold_offsetof_1 (t, stop_ref);

    default:
      gcc_unreachable ();
    }

  return size_binop (code, base, off);
}