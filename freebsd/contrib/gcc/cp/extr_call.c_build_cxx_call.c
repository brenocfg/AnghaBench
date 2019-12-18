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
struct TYPE_2__ {int can_throw; } ;

/* Variables and functions */
 scalar_t__ IS_AGGR_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_NOTHROW (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ VOID_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ at_function_scope_p () ; 
 scalar_t__ build_call (scalar_t__,scalar_t__) ; 
 scalar_t__ build_cplus_new (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ cfun ; 
 scalar_t__ convert_from_reference (scalar_t__) ; 
 TYPE_1__* cp_function_chain ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ fold_if_not_in_template (scalar_t__) ; 
 scalar_t__ get_callee_fndecl (scalar_t__) ; 
 scalar_t__ require_complete_type (scalar_t__) ; 

tree
build_cxx_call (tree fn, tree args)
{
  tree fndecl;

  fn = build_call (fn, args);

  /* If this call might throw an exception, note that fact.  */
  fndecl = get_callee_fndecl (fn);
  if ((!fndecl || !TREE_NOTHROW (fndecl))
      && at_function_scope_p ()
      && cfun)
    cp_function_chain->can_throw = 1;

  /* Some built-in function calls will be evaluated at compile-time in
     fold ().  */
  fn = fold_if_not_in_template (fn);

  if (VOID_TYPE_P (TREE_TYPE (fn)))
    return fn;

  fn = require_complete_type (fn);
  if (fn == error_mark_node)
    return error_mark_node;

  if (IS_AGGR_TYPE (TREE_TYPE (fn)))
    fn = build_cplus_new (TREE_TYPE (fn), fn);
  return convert_from_reference (fn);
}