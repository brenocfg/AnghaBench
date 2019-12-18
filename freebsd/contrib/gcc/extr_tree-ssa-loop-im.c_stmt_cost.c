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
 int /*<<< orphan*/  BUILT_IN_CONSTANT_P ; 
 int /*<<< orphan*/  BUILT_IN_NORMAL ; 
#define  CALL_EXPR 139 
#define  CEIL_DIV_EXPR 138 
#define  CEIL_MOD_EXPR 137 
 int COND_EXPR ; 
 int /*<<< orphan*/  DECL_BUILT_IN_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_FUNCTION_CODE (int /*<<< orphan*/ ) ; 
#define  EXACT_DIV_EXPR 136 
#define  FLOOR_DIV_EXPR 135 
#define  FLOOR_MOD_EXPR 134 
 int LIM_EXPENSIVE ; 
#define  MULT_EXPR 133 
#define  RDIV_EXPR 132 
#define  ROUND_DIV_EXPR 131 
#define  ROUND_MOD_EXPR 130 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
#define  TRUNC_DIV_EXPR 129 
#define  TRUNC_MOD_EXPR 128 
 int /*<<< orphan*/  get_callee_fndecl (int /*<<< orphan*/ ) ; 
 scalar_t__ stmt_references_memory_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
stmt_cost (tree stmt)
{
  tree rhs;
  unsigned cost = 1;

  /* Always try to create possibilities for unswitching.  */
  if (TREE_CODE (stmt) == COND_EXPR)
    return LIM_EXPENSIVE;

  rhs = TREE_OPERAND (stmt, 1);

  /* Hoisting memory references out should almost surely be a win.  */
  if (stmt_references_memory_p (stmt))
    cost += 20;

  switch (TREE_CODE (rhs))
    {
    case CALL_EXPR:
      /* We should be hoisting calls if possible.  */

      /* Unless the call is a builtin_constant_p; this always folds to a
	 constant, so moving it is useless.  */
      rhs = get_callee_fndecl (rhs);
      if (DECL_BUILT_IN_CLASS (rhs) == BUILT_IN_NORMAL
	  && DECL_FUNCTION_CODE (rhs) == BUILT_IN_CONSTANT_P)
	return 0;

      cost += 20;
      break;

    case MULT_EXPR:
    case TRUNC_DIV_EXPR:
    case CEIL_DIV_EXPR:
    case FLOOR_DIV_EXPR:
    case ROUND_DIV_EXPR:
    case EXACT_DIV_EXPR:
    case CEIL_MOD_EXPR:
    case FLOOR_MOD_EXPR:
    case ROUND_MOD_EXPR:
    case TRUNC_MOD_EXPR:
    case RDIV_EXPR:
      /* Division and multiplication are usually expensive.  */
      cost += 20;
      break;

    default:
      break;
    }

  return cost;
}