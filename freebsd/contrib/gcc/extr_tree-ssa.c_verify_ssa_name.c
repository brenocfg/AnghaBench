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
 scalar_t__ SSA_NAME ; 
 scalar_t__ SSA_NAME_IN_FREE_LIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSA_NAME_VAR (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * get_subvars_for_var (int /*<<< orphan*/ ) ; 
 scalar_t__ is_gimple_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ var_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
verify_ssa_name (tree ssa_name, bool is_virtual)
{
  if (TREE_CODE (ssa_name) != SSA_NAME)
    {
      error ("expected an SSA_NAME object");
      return true;
    }

  if (TREE_TYPE (ssa_name) != TREE_TYPE (SSA_NAME_VAR (ssa_name)))
    {
      error ("type mismatch between an SSA_NAME and its symbol");
      return true;
    }

  if (SSA_NAME_IN_FREE_LIST (ssa_name))
    {
      error ("found an SSA_NAME that had been released into the free pool");
      return true;
    }

  if (is_virtual && is_gimple_reg (ssa_name))
    {
      error ("found a virtual definition for a GIMPLE register");
      return true;
    }

  if (!is_virtual && !is_gimple_reg (ssa_name))
    {
      error ("found a real definition for a non-register");
      return true;
    }

  if (is_virtual && var_ann (SSA_NAME_VAR (ssa_name)) 
      && get_subvars_for_var (SSA_NAME_VAR (ssa_name)) != NULL)
    {
      error ("found real variable when subvariables should have appeared");
      return true;
    }

  return false;
}