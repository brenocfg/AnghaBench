#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  scalar_t__ tag_scope ;
struct cp_binding_level {scalar_t__ kind; scalar_t__ this_entity; struct cp_binding_level* level_chain; } ;
struct TYPE_7__ {struct cp_binding_level* scope; scalar_t__ value; scalar_t__ type; } ;
typedef  TYPE_1__ cxx_binding ;

/* Variables and functions */
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 int /*<<< orphan*/  INHERITED_VALUE_BINDING_P (TYPE_1__*) ; 
 scalar_t__ LOCAL_BINDING_P (TYPE_1__*) ; 
 int /*<<< orphan*/  LOOKUP_PREFER_TYPES ; 
 int /*<<< orphan*/  NAMESPACE_LEVEL (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  POP_TIMEVAR_AND_RETURN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TV_NAME_LOOKUP ; 
 struct cp_binding_level* current_binding_level ; 
 int /*<<< orphan*/  current_decl_namespace () ; 
 TYPE_1__* cxx_scope_find_binding_for_name (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* outer_binding (scalar_t__,TYPE_1__*,int) ; 
 scalar_t__ qualify_lookup (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ sk_class ; 
 scalar_t__ sk_cleanup ; 
 scalar_t__ sk_namespace ; 
 scalar_t__ sk_template_parms ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 
 scalar_t__ ts_current ; 
 scalar_t__ ts_within_enclosing_non_class ; 

tree
lookup_type_scope (tree name, tag_scope scope)
{
  cxx_binding *iter = NULL;
  tree val = NULL_TREE;

  timevar_push (TV_NAME_LOOKUP);

  /* Look in non-namespace scope first.  */
  if (current_binding_level->kind != sk_namespace)
    iter = outer_binding (name, NULL, /*class_p=*/ true);
  for (; iter; iter = outer_binding (name, iter, /*class_p=*/ true))
    {
      /* Check if this is the kind of thing we're looking for.
	 If SCOPE is TS_CURRENT, also make sure it doesn't come from
	 base class.  For ITER->VALUE, we can simply use
	 INHERITED_VALUE_BINDING_P.  For ITER->TYPE, we have to use
	 our own check.

	 We check ITER->TYPE before ITER->VALUE in order to handle
	   typedef struct C {} C;
	 correctly.  */

      if (qualify_lookup (iter->type, LOOKUP_PREFER_TYPES)
	  && (scope != ts_current
	      || LOCAL_BINDING_P (iter)
	      || DECL_CONTEXT (iter->type) == iter->scope->this_entity))
	val = iter->type;
      else if ((scope != ts_current
		|| !INHERITED_VALUE_BINDING_P (iter))
	       && qualify_lookup (iter->value, LOOKUP_PREFER_TYPES))
	val = iter->value;

      if (val)
	break;
    }

  /* Look in namespace scope.  */
  if (!val)
    {
      iter = cxx_scope_find_binding_for_name
	       (NAMESPACE_LEVEL (current_decl_namespace ()), name);

      if (iter)
	{
	  /* If this is the kind of thing we're looking for, we're done.  */
	  if (qualify_lookup (iter->type, LOOKUP_PREFER_TYPES))
	    val = iter->type;
	  else if (qualify_lookup (iter->value, LOOKUP_PREFER_TYPES))
	    val = iter->value;
	}

    }

  /* Type found, check if it is in the allowed scopes, ignoring cleanup
     and template parameter scopes.  */
  if (val)
    {
      struct cp_binding_level *b = current_binding_level;
      while (b)
	{
	  if (iter->scope == b)
	    POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, val);

	  if (b->kind == sk_cleanup || b->kind == sk_template_parms)
	    b = b->level_chain;
	  else if (b->kind == sk_class
		   && scope == ts_within_enclosing_non_class)
	    b = b->level_chain;
	  else
	    break;
	}
    }

  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, NULL_TREE);
}