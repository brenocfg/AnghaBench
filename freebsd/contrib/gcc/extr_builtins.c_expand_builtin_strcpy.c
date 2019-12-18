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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ COMPOUND_EXPR ; 
 int /*<<< orphan*/  EXPAND_NORMAL ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  expand_expr (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_movstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fold_builtin_strcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ validate_arglist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_strcpy (tree fndecl, tree arglist, rtx target, enum machine_mode mode)
{
  if (validate_arglist (arglist, POINTER_TYPE, POINTER_TYPE, VOID_TYPE))
    {
      tree result = fold_builtin_strcpy (fndecl, arglist, 0);
      if (result)
	{
	  while (TREE_CODE (result) == COMPOUND_EXPR)
	    {
	      expand_expr (TREE_OPERAND (result, 0), const0_rtx, VOIDmode,
			   EXPAND_NORMAL);
	      result = TREE_OPERAND (result, 1);
	    }
	  return expand_expr (result, target, mode, EXPAND_NORMAL);
	}

      return expand_movstr (TREE_VALUE (arglist),
			    TREE_VALUE (TREE_CHAIN (arglist)),
			    target, /*endp=*/0);
    }
  return 0;
}