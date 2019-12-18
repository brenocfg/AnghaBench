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
 int /*<<< orphan*/  ABS_EXPR ; 
 scalar_t__ REAL_CST ; 
 int /*<<< orphan*/  REAL_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  fold_abs_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_fabs (tree arglist, tree type)
{
  tree arg;

  if (!validate_arglist (arglist, REAL_TYPE, VOID_TYPE))
    return 0;

  arg = TREE_VALUE (arglist);
  arg = fold_convert (type, arg);
  if (TREE_CODE (arg) == REAL_CST)
    return fold_abs_const (arg, type);
  return fold_build1 (ABS_EXPR, type, arg);
}