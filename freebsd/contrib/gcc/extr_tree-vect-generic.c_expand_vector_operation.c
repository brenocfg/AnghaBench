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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
#define  BIT_AND_EXPR 134 
#define  BIT_IOR_EXPR 133 
#define  BIT_NOT_EXPR 132 
#define  BIT_XOR_EXPR 131 
 scalar_t__ GET_MODE_CLASS (int) ; 
#define  MINUS_EXPR 130 
 scalar_t__ MODE_VECTOR_FLOAT ; 
 scalar_t__ MODE_VECTOR_INT ; 
#define  NEGATE_EXPR 129 
 int /*<<< orphan*/  NULL_TREE ; 
#define  PLUS_EXPR 128 
 scalar_t__ TREE_CODE_CLASS (int) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_OVERFLOW_TRAPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_binop ; 
 int /*<<< orphan*/  do_negate ; 
 int /*<<< orphan*/  do_plus_minus ; 
 int /*<<< orphan*/  do_unop ; 
 int /*<<< orphan*/  expand_vector_addition (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expand_vector_parallel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expand_vector_piecewise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tcc_unary ; 

__attribute__((used)) static tree
expand_vector_operation (block_stmt_iterator *bsi, tree type, tree compute_type,
			 tree rhs, enum tree_code code)
{
  enum machine_mode compute_mode = TYPE_MODE (compute_type);

  /* If the compute mode is not a vector mode (hence we are not decomposing
     a BLKmode vector to smaller, hardware-supported vectors), we may want
     to expand the operations in parallel.  */
  if (GET_MODE_CLASS (compute_mode) != MODE_VECTOR_INT
      && GET_MODE_CLASS (compute_mode) != MODE_VECTOR_FLOAT)
    switch (code)
      {
      case PLUS_EXPR:
      case MINUS_EXPR:
        if (!TYPE_OVERFLOW_TRAPS (type))
          return expand_vector_addition (bsi, do_binop, do_plus_minus, type,
		      		         TREE_OPERAND (rhs, 0),
					 TREE_OPERAND (rhs, 1), code);
	break;

      case NEGATE_EXPR:
        if (!TYPE_OVERFLOW_TRAPS (type))
          return expand_vector_addition (bsi, do_unop, do_negate, type,
		      		         TREE_OPERAND (rhs, 0),
					 NULL_TREE, code);
	break;

      case BIT_AND_EXPR:
      case BIT_IOR_EXPR:
      case BIT_XOR_EXPR:
        return expand_vector_parallel (bsi, do_binop, type,
		      		       TREE_OPERAND (rhs, 0),
				       TREE_OPERAND (rhs, 1), code);

      case BIT_NOT_EXPR:
        return expand_vector_parallel (bsi, do_unop, type,
		      		       TREE_OPERAND (rhs, 0),
				       NULL_TREE, code);

      default:
	break;
      }

  if (TREE_CODE_CLASS (code) == tcc_unary)
    return expand_vector_piecewise (bsi, do_unop, type, compute_type,
				    TREE_OPERAND (rhs, 0),
				    NULL_TREE, code);
  else
    return expand_vector_piecewise (bsi, do_binop, type, compute_type,
				    TREE_OPERAND (rhs, 0),
				    TREE_OPERAND (rhs, 1), code);
}