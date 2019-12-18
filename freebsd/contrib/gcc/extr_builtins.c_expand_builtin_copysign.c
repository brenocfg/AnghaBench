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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  EXPAND_NORMAL ; 
 int /*<<< orphan*/  REAL_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  expand_copysign (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_normal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_copysign (tree arglist, rtx target, rtx subtarget)
{
  rtx op0, op1;
  tree arg;

  if (!validate_arglist (arglist, REAL_TYPE, REAL_TYPE, VOID_TYPE))
    return 0;

  arg = TREE_VALUE (arglist);
  op0 = expand_expr (arg, subtarget, VOIDmode, EXPAND_NORMAL);

  arg = TREE_VALUE (TREE_CHAIN (arglist));
  op1 = expand_normal (arg);

  return expand_copysign (op0, op1, target);
}