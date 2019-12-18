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
typedef  int /*<<< orphan*/  subvar_t ;

/* Variables and functions */
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_VAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSA_VAR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lookup_subvars_for_var (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline subvar_t
get_subvars_for_var (tree var)
{
  subvar_t subvars;

  gcc_assert (SSA_VAR_P (var));  
  
  if (TREE_CODE (var) == SSA_NAME)
    subvars = *(lookup_subvars_for_var (SSA_NAME_VAR (var)));
  else
    subvars = *(lookup_subvars_for_var (var));
  return subvars;
}