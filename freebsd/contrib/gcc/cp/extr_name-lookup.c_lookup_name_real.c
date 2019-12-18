#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct cp_binding_level {scalar_t__ kind; scalar_t__ this_entity; struct cp_binding_level* level_chain; } ;
struct TYPE_5__ {scalar_t__ value; scalar_t__ type; } ;
typedef  TYPE_1__ cxx_binding ;

/* Variables and functions */
 scalar_t__ IDENTIFIER_TYPENAME_P (scalar_t__) ; 
 scalar_t__ LOCAL_BINDING_P (TYPE_1__*) ; 
 scalar_t__ LOCAL_CLASS_P (scalar_t__) ; 
 int LOOKUP_PREFER_TYPES ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ OVERLOAD ; 
 scalar_t__ OVL_FUNCTION (scalar_t__) ; 
 int /*<<< orphan*/  POP_TIMEVAR_AND_RETURN (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TV_NAME_LOOKUP ; 
 struct cp_binding_level* current_binding_level ; 
 scalar_t__ current_class_type ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ hidden_name_p (scalar_t__) ; 
 int lookup_flags (int,int) ; 
 scalar_t__ lookup_fnfields (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* outer_binding (scalar_t__,TYPE_1__*,int) ; 
 scalar_t__ qualify_lookup (scalar_t__,int) ; 
 int /*<<< orphan*/  really_overloaded_fn (scalar_t__) ; 
 scalar_t__ sk_class ; 
 scalar_t__ sk_namespace ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 
 scalar_t__ unqualified_namespace_lookup (scalar_t__,int) ; 

tree
lookup_name_real (tree name, int prefer_type, int nonclass, bool block_p,
		  int namespaces_only, int flags)
{
  cxx_binding *iter;
  tree val = NULL_TREE;

  timevar_push (TV_NAME_LOOKUP);
  /* Conversion operators are handled specially because ordinary
     unqualified name lookup will not find template conversion
     operators.  */
  if (IDENTIFIER_TYPENAME_P (name))
    {
      struct cp_binding_level *level;

      for (level = current_binding_level;
	   level && level->kind != sk_namespace;
	   level = level->level_chain)
	{
	  tree class_type;
	  tree operators;

	  /* A conversion operator can only be declared in a class
	     scope.  */
	  if (level->kind != sk_class)
	    continue;

	  /* Lookup the conversion operator in the class.  */
	  class_type = level->this_entity;
	  operators = lookup_fnfields (class_type, name, /*protect=*/0);
	  if (operators)
	    POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, operators);
	}

      POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, NULL_TREE);
    }

  flags |= lookup_flags (prefer_type, namespaces_only);

  /* First, look in non-namespace scopes.  */

  if (current_class_type == NULL_TREE)
    nonclass = 1;

  if (block_p || !nonclass)
    for (iter = outer_binding (name, NULL, !nonclass);
	 iter;
	 iter = outer_binding (name, iter, !nonclass))
      {
	tree binding;

	/* Skip entities we don't want.  */
	if (LOCAL_BINDING_P (iter) ? !block_p : nonclass)
	  continue;

	/* If this is the kind of thing we're looking for, we're done.  */
	if (qualify_lookup (iter->value, flags))
	  binding = iter->value;
	else if ((flags & LOOKUP_PREFER_TYPES)
		 && qualify_lookup (iter->type, flags))
	  binding = iter->type;
	else
	  binding = NULL_TREE;

	if (binding)
	  {
	    if (hidden_name_p (binding))
	      {
		/* A non namespace-scope binding can only be hidden if
		   we are in a local class, due to friend declarations.
		   In particular, consider:

		   void f() {
		     struct A {
		       friend struct B;
		       void g() { B* b; } // error: B is hidden
		     }
		     struct B {};
		   }

		   The standard says that "B" is a local class in "f"
		   (but not nested within "A") -- but that name lookup
		   for "B" does not find this declaration until it is
		   declared directly with "f".

		   In particular:

		   [class.friend]

		   If a friend declaration appears in a local class and
		   the name specified is an unqualified name, a prior
		   declaration is looked up without considering scopes
		   that are outside the innermost enclosing non-class
		   scope. For a friend class declaration, if there is no
		   prior declaration, the class that is specified 
		   belongs to the innermost enclosing non-class scope,
		   but if it is subsequently referenced, its name is not
		   found by name lookup until a matching declaration is
		   provided in the innermost enclosing nonclass scope.
		*/
		gcc_assert (current_class_type &&
			    LOCAL_CLASS_P (current_class_type));

		/* This binding comes from a friend declaration in the local
		   class. The standard (11.4.8) states that the lookup can
		   only succeed if there is a non-hidden declaration in the
		   current scope, which is not the case here.  */
		POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, NULL_TREE);
	      }
	    val = binding;
	    break;
	  }
      }

  /* Now lookup in namespace scopes.  */
  if (!val)
    val = unqualified_namespace_lookup (name, flags);

  /* If we have a single function from a using decl, pull it out.  */
  if (val && TREE_CODE (val) == OVERLOAD && !really_overloaded_fn (val))
    val = OVL_FUNCTION (val);

  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, val);
}