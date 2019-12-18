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

/* Variables and functions */
 int /*<<< orphan*/  EXPAND_NORMAL ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  expand_expr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fold_builtin_fputs (scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ validate_arglist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_fputs (tree arglist, rtx target, bool unlocked)
{
  /* Verify the arguments in the original call.  */
  if (validate_arglist (arglist, POINTER_TYPE, POINTER_TYPE, VOID_TYPE))
    {
      tree result = fold_builtin_fputs (arglist, (target == const0_rtx),
					unlocked, NULL_TREE);
      if (result)
	return expand_expr (result, target, VOIDmode, EXPAND_NORMAL);
    }
  return 0;
}