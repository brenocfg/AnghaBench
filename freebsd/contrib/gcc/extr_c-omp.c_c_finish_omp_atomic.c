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
 scalar_t__ ADDR_EXPR ; 
 int /*<<< orphan*/  INTEGRAL_TYPE_P (scalar_t__) ; 
 scalar_t__ MODIFY_EXPR ; 
 int /*<<< orphan*/  OMP_ATOMIC ; 
 int /*<<< orphan*/  POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ SAVE_EXPR ; 
 int /*<<< orphan*/  SCALAR_FLOAT_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  TARGET_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build4 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ build_indirect_ref (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ build_modify_expr (scalar_t__,int,scalar_t__) ; 
 scalar_t__ build_unary_op (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ create_tmp_var_raw (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ save_expr (scalar_t__) ; 
 int /*<<< orphan*/  void_type_node ; 

tree
c_finish_omp_atomic (enum tree_code code, tree lhs, tree rhs)
{
  tree x, type, addr;

  if (lhs == error_mark_node || rhs == error_mark_node)
    return error_mark_node;

  /* ??? According to one reading of the OpenMP spec, complex type are
     supported, but there are no atomic stores for any architecture.
     But at least icc 9.0 doesn't support complex types here either.
     And lets not even talk about vector types...  */
  type = TREE_TYPE (lhs);
  if (!INTEGRAL_TYPE_P (type)
      && !POINTER_TYPE_P (type)
      && !SCALAR_FLOAT_TYPE_P (type))
    {
      error ("invalid expression type for %<#pragma omp atomic%>");
      return error_mark_node;
    }

  /* ??? Validate that rhs does not overlap lhs.  */

  /* Take and save the address of the lhs.  From then on we'll reference it
     via indirection.  */
  addr = build_unary_op (ADDR_EXPR, lhs, 0);
  if (addr == error_mark_node)
    return error_mark_node;
  addr = save_expr (addr);
  if (TREE_CODE (addr) != SAVE_EXPR
      && (TREE_CODE (addr) != ADDR_EXPR
	  || TREE_CODE (TREE_OPERAND (addr, 0)) != VAR_DECL))
    {
      /* Make sure LHS is simple enough so that goa_lhs_expr_p can recognize
	 it even after unsharing function body.  */
      tree var = create_tmp_var_raw (TREE_TYPE (addr), NULL);
      addr = build4 (TARGET_EXPR, TREE_TYPE (addr), var, addr, NULL, NULL);
    }
  lhs = build_indirect_ref (addr, NULL);

  /* There are lots of warnings, errors, and conversions that need to happen
     in the course of interpreting a statement.  Use the normal mechanisms
     to do this, and then take it apart again.  */
  x = build_modify_expr (lhs, code, rhs);
  if (x == error_mark_node)
    return error_mark_node;
  gcc_assert (TREE_CODE (x) == MODIFY_EXPR);  
  rhs = TREE_OPERAND (x, 1);

  /* Punt the actual generation of atomic operations to common code.  */
  return build2 (OMP_ATOMIC, void_type_node, addr, rhs);
}