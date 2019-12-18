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
 scalar_t__ NULL_TREE ; 
 scalar_t__ OVERLOAD ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
 scalar_t__ OVL_FUNCTION (scalar_t__) ; 
 scalar_t__ OVL_NEXT (scalar_t__) ; 
 int PUSH_LOCAL ; 
 int PUSH_USING ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  add_decl_expr (scalar_t__) ; 
 scalar_t__ at_function_scope_p () ; 
 scalar_t__ building_stmt_tree () ; 
 int /*<<< orphan*/  cp_emit_debug_info_for_using (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_scope () ; 
 int /*<<< orphan*/  do_nonmember_using_decl (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 scalar_t__ is_overloaded_fn (scalar_t__) ; 
 scalar_t__ lookup_name_innermost_nonclass_level (scalar_t__) ; 
 scalar_t__ lookup_type_current_level (scalar_t__) ; 
 int /*<<< orphan*/  processing_template_decl ; 
 int /*<<< orphan*/  push_local_binding (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  push_overloaded_decl (scalar_t__,int,int) ; 
 int /*<<< orphan*/  set_identifier_type_value (scalar_t__,scalar_t__) ; 
 scalar_t__ validate_nonmember_using_decl (scalar_t__,scalar_t__,scalar_t__) ; 

void
do_local_using_decl (tree decl, tree scope, tree name)
{
  tree oldval, oldtype, newval, newtype;
  tree orig_decl = decl;

  decl = validate_nonmember_using_decl (decl, scope, name);
  if (decl == NULL_TREE)
    return;

  if (building_stmt_tree ()
      && at_function_scope_p ())
    add_decl_expr (decl);

  oldval = lookup_name_innermost_nonclass_level (name);
  oldtype = lookup_type_current_level (name);

  do_nonmember_using_decl (scope, name, oldval, oldtype, &newval, &newtype);

  if (newval)
    {
      if (is_overloaded_fn (newval))
	{
	  tree fn, term;

	  /* We only need to push declarations for those functions
	     that were not already bound in the current level.
	     The old value might be NULL_TREE, it might be a single
	     function, or an OVERLOAD.  */
	  if (oldval && TREE_CODE (oldval) == OVERLOAD)
	    term = OVL_FUNCTION (oldval);
	  else
	    term = oldval;
	  for (fn = newval; fn && OVL_CURRENT (fn) != term;
	       fn = OVL_NEXT (fn))
	    push_overloaded_decl (OVL_CURRENT (fn),
				  PUSH_LOCAL | PUSH_USING,
				  false);
	}
      else
	push_local_binding (name, newval, PUSH_USING);
    }
  if (newtype)
    {
      push_local_binding (name, newtype, PUSH_USING);
      set_identifier_type_value (name, newtype);
    }

  /* Emit debug info.  */
  if (!processing_template_decl)
    cp_emit_debug_info_for_using (orig_decl, current_scope());
}