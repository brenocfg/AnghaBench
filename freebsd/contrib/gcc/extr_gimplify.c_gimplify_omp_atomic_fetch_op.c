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
typedef  int /*<<< orphan*/ * tree ;
typedef  enum insn_code { ____Placeholder_insn_code } insn_code ;
typedef  enum gimplify_status { ____Placeholder_gimplify_status } gimplify_status ;
typedef  enum built_in_function { ____Placeholder_built_in_function } built_in_function ;

/* Variables and functions */
#define  BIT_AND_EXPR 132 
#define  BIT_IOR_EXPR 131 
#define  BIT_XOR_EXPR 130 
 int BUILT_IN_FETCH_AND_ADD_N ; 
 int BUILT_IN_FETCH_AND_AND_N ; 
 int BUILT_IN_FETCH_AND_OR_N ; 
 int BUILT_IN_FETCH_AND_SUB_N ; 
 int BUILT_IN_FETCH_AND_XOR_N ; 
 int CODE_FOR_nothing ; 
 int GS_OK ; 
 int GS_UNHANDLED ; 
#define  MINUS_EXPR 129 
#define  PLUS_EXPR 128 
 int TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ *) ; 
 size_t TYPE_MODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_function_call_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** built_in_decls ; 
 scalar_t__ commutative_tree_code (int) ; 
 int /*<<< orphan*/ * fold_convert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ goa_lhs_expr_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int* sync_add_optab ; 
 int* sync_and_optab ; 
 int* sync_ior_optab ; 
 int* sync_xor_optab ; 
 int /*<<< orphan*/ * tree_cons (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum gimplify_status
gimplify_omp_atomic_fetch_op (tree *expr_p, tree addr, tree rhs, int index)
{
  enum built_in_function base;
  tree decl, args, itype;
  enum insn_code *optab;

  /* Check for one of the supported fetch-op operations.  */
  switch (TREE_CODE (rhs))
    {
    case PLUS_EXPR:
      base = BUILT_IN_FETCH_AND_ADD_N;
      optab = sync_add_optab;
      break;
    case MINUS_EXPR:
      base = BUILT_IN_FETCH_AND_SUB_N;
      optab = sync_add_optab;
      break;
    case BIT_AND_EXPR:
      base = BUILT_IN_FETCH_AND_AND_N;
      optab = sync_and_optab;
      break;
    case BIT_IOR_EXPR:
      base = BUILT_IN_FETCH_AND_OR_N;
      optab = sync_ior_optab;
      break;
    case BIT_XOR_EXPR:
      base = BUILT_IN_FETCH_AND_XOR_N;
      optab = sync_xor_optab;
      break;
    default:
      return GS_UNHANDLED;
    }

  /* Make sure the expression is of the proper form.  */
  if (goa_lhs_expr_p (TREE_OPERAND (rhs, 0), addr))
    rhs = TREE_OPERAND (rhs, 1);
  else if (commutative_tree_code (TREE_CODE (rhs))
	   && goa_lhs_expr_p (TREE_OPERAND (rhs, 1), addr))
    rhs = TREE_OPERAND (rhs, 0);
  else
    return GS_UNHANDLED;

  decl = built_in_decls[base + index + 1];
  itype = TREE_TYPE (TREE_TYPE (decl));

  if (optab[TYPE_MODE (itype)] == CODE_FOR_nothing)
    return GS_UNHANDLED;

  args = tree_cons (NULL, fold_convert (itype, rhs), NULL);
  args = tree_cons (NULL, addr, args);
  *expr_p = build_function_call_expr (decl, args);
  return GS_OK;
}