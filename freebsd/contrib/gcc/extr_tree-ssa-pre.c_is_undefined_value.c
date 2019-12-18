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
 scalar_t__ IS_EMPTY_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ PARM_DECL ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSA_NAME_VAR (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
is_undefined_value (tree expr)
{
  return (TREE_CODE (expr) == SSA_NAME
          && IS_EMPTY_STMT (SSA_NAME_DEF_STMT (expr))
	  /* PARM_DECLs and hard registers are always defined.  */
	  && TREE_CODE (SSA_NAME_VAR (expr)) != PARM_DECL);
}