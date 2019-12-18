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
 scalar_t__ DECL_NAME (int /*<<< orphan*/ ) ; 
 char const* IDENTIFIER_POINTER (scalar_t__) ; 
 scalar_t__ PARM_DECL ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ find_first_artificial_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ssa_base (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
get_var_name (tree var)
{
  if (TREE_CODE (var) == SSA_NAME)
    return get_var_name (get_ssa_base (var));

  if (find_first_artificial_name (var))
    return "{unknown}";

  if (TREE_CODE (var) == VAR_DECL || TREE_CODE (var) == PARM_DECL)
    if (DECL_NAME (var))
      return IDENTIFIER_POINTER (DECL_NAME (var));

  return "{unknown}";
}