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

/* Variables and functions */
 scalar_t__ DECL_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ SSA_NAME_VAR (scalar_t__) ; 
 scalar_t__ get_current_def (scalar_t__) ; 
 scalar_t__ get_default_def_for (scalar_t__) ; 
 int /*<<< orphan*/  set_current_def (scalar_t__,scalar_t__) ; 

__attribute__((used)) static tree
get_reaching_def (tree var)
{
  tree currdef_var, avar;
  
  /* Lookup the current reaching definition for VAR.  */
  currdef_var = get_current_def (var);

  /* If there is no reaching definition for VAR, create and register a
     default definition for it (if needed).  */
  if (currdef_var == NULL_TREE)
    {
      avar = DECL_P (var) ? var : SSA_NAME_VAR (var);
      currdef_var = get_default_def_for (avar);
      set_current_def (var, currdef_var);
    }

  /* Return the current reaching definition for VAR, or the default
     definition, if we had to create one.  */
  return currdef_var;
}