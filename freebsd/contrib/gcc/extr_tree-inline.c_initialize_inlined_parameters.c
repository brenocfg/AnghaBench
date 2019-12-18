#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_8__ {int /*<<< orphan*/  block; } ;
typedef  TYPE_2__ copy_body_data ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_10__ {scalar_t__ static_chain_decl; } ;
struct TYPE_7__ {scalar_t__ (* convert_parm_for_inlining ) (scalar_t__,scalar_t__,scalar_t__,int) ;} ;
struct TYPE_9__ {TYPE_1__ tree_inlining; } ;

/* Variables and functions */
 scalar_t__ DECL_ARGUMENTS (scalar_t__) ; 
 TYPE_6__* DECL_STRUCT_FUNCTION (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ current_function_decl ; 
 int /*<<< orphan*/  declare_inline_vars (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 TYPE_4__ lang_hooks ; 
 int /*<<< orphan*/  setup_one_parameter (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void
initialize_inlined_parameters (copy_body_data *id, tree args, tree static_chain,
			       tree fn, basic_block bb)
{
  tree parms;
  tree a;
  tree p;
  tree vars = NULL_TREE;
  int argnum = 0;

  /* Figure out what the parameters are.  */
  parms = DECL_ARGUMENTS (fn);

  /* Loop through the parameter declarations, replacing each with an
     equivalent VAR_DECL, appropriately initialized.  */
  for (p = parms, a = args; p;
       a = a ? TREE_CHAIN (a) : a, p = TREE_CHAIN (p))
    {
      tree value;

      ++argnum;

      /* Find the initializer.  */
      value = lang_hooks.tree_inlining.convert_parm_for_inlining
	      (p, a ? TREE_VALUE (a) : NULL_TREE, fn, argnum);

      setup_one_parameter (id, p, value, fn, bb, &vars);
    }

  /* Initialize the static chain.  */
  p = DECL_STRUCT_FUNCTION (fn)->static_chain_decl;
  gcc_assert (fn != current_function_decl);
  if (p)
    {
      /* No static chain?  Seems like a bug in tree-nested.c.  */
      gcc_assert (static_chain);

      setup_one_parameter (id, p, static_chain, fn, bb, &vars);
    }

  declare_inline_vars (id->block, vars);
}