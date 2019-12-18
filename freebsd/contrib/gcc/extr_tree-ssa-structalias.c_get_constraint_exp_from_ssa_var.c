#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct constraint_expr {scalar_t__ var; scalar_t__ offset; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESSOF ; 
 scalar_t__ DECL_P (scalar_t__) ; 
 scalar_t__ PARM_DECL ; 
 int /*<<< orphan*/  SCALAR ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ SSA_NAME_VAR (scalar_t__) ; 
 scalar_t__ SSA_VAR_P (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_READONLY (scalar_t__) ; 
 scalar_t__ anything_id ; 
 scalar_t__ default_def (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__* get_vi_for_tree (scalar_t__) ; 
 scalar_t__ readonly_id ; 

__attribute__((used)) static struct constraint_expr
get_constraint_exp_from_ssa_var (tree t)
{
  struct constraint_expr cexpr;

  gcc_assert (SSA_VAR_P (t) || DECL_P (t));

  /* For parameters, get at the points-to set for the actual parm
     decl.  */
  if (TREE_CODE (t) == SSA_NAME
      && TREE_CODE (SSA_NAME_VAR (t)) == PARM_DECL
      && default_def (SSA_NAME_VAR (t)) == t)
    return get_constraint_exp_from_ssa_var (SSA_NAME_VAR (t));

  cexpr.type = SCALAR;

  cexpr.var = get_vi_for_tree (t)->id;
  /* If we determine the result is "anything", and we know this is readonly,
     say it points to readonly memory instead.  */
  if (cexpr.var == anything_id && TREE_READONLY (t))
    {
      cexpr.type = ADDRESSOF;
      cexpr.var = readonly_id;
    }

  cexpr.offset = 0;
  return cexpr;
}