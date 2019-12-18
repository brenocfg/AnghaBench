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
 scalar_t__ PARM_DECL ; 
 scalar_t__ TREE_ADDRESSABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_STATIC (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  save_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
builtin_save_expr (tree exp)
{
  if (TREE_ADDRESSABLE (exp) == 0
      && (TREE_CODE (exp) == PARM_DECL
	  || (TREE_CODE (exp) == VAR_DECL && !TREE_STATIC (exp))))
    return exp;

  return save_expr (exp);
}