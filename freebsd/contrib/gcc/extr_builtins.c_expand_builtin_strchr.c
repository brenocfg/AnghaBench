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
 int /*<<< orphan*/  EXPAND_NORMAL ; 
 int /*<<< orphan*/  INTEGER_TYPE ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  expand_expr (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ fold_builtin_strchr (scalar_t__,scalar_t__) ; 
 scalar_t__ validate_arglist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_strchr (tree arglist, tree type, rtx target, enum machine_mode mode)
{
  if (validate_arglist (arglist, POINTER_TYPE, INTEGER_TYPE, VOID_TYPE))
    {
      tree result = fold_builtin_strchr (arglist, type);
      if (result)
	return expand_expr (result, target, mode, EXPAND_NORMAL);

      /* FIXME: Should use strchrM optab so that ports can optimize this.  */
    }
  return 0;
}