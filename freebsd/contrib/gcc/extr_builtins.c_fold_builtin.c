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
typedef  int TREE_NO_WARNING ;

/* Variables and functions */
 int /*<<< orphan*/  NOP_EXPR ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ fold_builtin_1 (scalar_t__,scalar_t__,int) ; 

tree
fold_builtin (tree fndecl, tree arglist, bool ignore)
{
  tree exp = fold_builtin_1 (fndecl, arglist, ignore);
  if (exp)
    {
      exp = build1 (NOP_EXPR, TREE_TYPE (exp), exp);
      TREE_NO_WARNING (exp) = 1;
    }

  return exp;
}