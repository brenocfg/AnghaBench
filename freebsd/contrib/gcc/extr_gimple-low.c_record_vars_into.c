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
struct function {int /*<<< orphan*/  unexpanded_var_list; } ;

/* Variables and functions */
 scalar_t__ DECL_EXTERNAL (scalar_t__) ; 
 struct function* DECL_STRUCT_FUNCTION (scalar_t__) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 struct function* cfun ; 
 scalar_t__ current_function_decl ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void
record_vars_into (tree vars, tree fn)
{
  struct function *saved_cfun = cfun;

  if (fn != current_function_decl)
    cfun = DECL_STRUCT_FUNCTION (fn);

  for (; vars; vars = TREE_CHAIN (vars))
    {
      tree var = vars;

      /* BIND_EXPRs contains also function/type/constant declarations
         we don't need to care about.  */
      if (TREE_CODE (var) != VAR_DECL)
	continue;

      /* Nothing to do in this case.  */
      if (DECL_EXTERNAL (var))
	continue;

      /* Record the variable.  */
      cfun->unexpanded_var_list = tree_cons (NULL_TREE, var,
					     cfun->unexpanded_var_list);
    }

  if (fn != current_function_decl)
    cfun = saved_cfun;
}