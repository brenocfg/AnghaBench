#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_5__ {scalar_t__ value; int value_is_inherited; TYPE_1__* scope; scalar_t__ type; } ;
typedef  TYPE_2__ cxx_binding ;
struct TYPE_4__ {scalar_t__ kind; } ;

/* Variables and functions */
 scalar_t__ DECL_ANTICIPATED (scalar_t__) ; 
 scalar_t__ DECL_ARTIFICIAL (scalar_t__) ; 
 int /*<<< orphan*/  DECL_CLASS_SCOPE_P (scalar_t__) ; 
 scalar_t__ DECL_EXTERNAL (scalar_t__) ; 
 int /*<<< orphan*/  DECL_HIDDEN_FRIEND_P (scalar_t__) ; 
 scalar_t__ DECL_NAME (scalar_t__) ; 
 scalar_t__ DECL_NAMESPACE_ALIAS (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NAMESPACE_DECL ; 
 scalar_t__ ORIGINAL_NAMESPACE (scalar_t__) ; 
 int /*<<< orphan*/  POP_TIMEVAR_AND_RETURN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TV_NAME_LOOKUP ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  duplicate_decls (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sk_class ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 
 scalar_t__ uses_template_parms (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
supplement_binding (cxx_binding *binding, tree decl)
{
  tree bval = binding->value;
  bool ok = true;

  timevar_push (TV_NAME_LOOKUP);
  if (TREE_CODE (decl) == TYPE_DECL && DECL_ARTIFICIAL (decl))
    /* The new name is the type name.  */
    binding->type = decl;
  else if (/* BVAL is null when push_class_level_binding moves an
	      inherited type-binding out of the way to make room for a
	      new value binding.  */
	   !bval
	   /* BVAL is error_mark_node when DECL's name has been used
	      in a non-class scope prior declaration.  In that case,
	      we should have already issued a diagnostic; for graceful
	      error recovery purpose, pretend this was the intended
	      declaration for that name.  */
	   || bval == error_mark_node
	   /* If BVAL is anticipated but has not yet been declared,
	      pretend it is not there at all.  */
	   || (TREE_CODE (bval) == FUNCTION_DECL
	       && DECL_ANTICIPATED (bval)
	       && !DECL_HIDDEN_FRIEND_P (bval)))
    binding->value = decl;
  else if (TREE_CODE (bval) == TYPE_DECL && DECL_ARTIFICIAL (bval))
    {
      /* The old binding was a type name.  It was placed in
	 VALUE field because it was thought, at the point it was
	 declared, to be the only entity with such a name.  Move the
	 type name into the type slot; it is now hidden by the new
	 binding.  */
      binding->type = bval;
      binding->value = decl;
      binding->value_is_inherited = false;
    }
  else if (TREE_CODE (bval) == TYPE_DECL
	   && TREE_CODE (decl) == TYPE_DECL
	   && DECL_NAME (decl) == DECL_NAME (bval)
	   && binding->scope->kind != sk_class
	   && (same_type_p (TREE_TYPE (decl), TREE_TYPE (bval))
	       /* If either type involves template parameters, we must
		  wait until instantiation.  */
	       || uses_template_parms (TREE_TYPE (decl))
	       || uses_template_parms (TREE_TYPE (bval))))
    /* We have two typedef-names, both naming the same type to have
       the same name.  In general, this is OK because of:

	 [dcl.typedef]

	 In a given scope, a typedef specifier can be used to redefine
	 the name of any type declared in that scope to refer to the
	 type to which it already refers.

       However, in class scopes, this rule does not apply due to the
       stricter language in [class.mem] prohibiting redeclarations of
       members.  */
    ok = false;
  /* There can be two block-scope declarations of the same variable,
     so long as they are `extern' declarations.  However, there cannot
     be two declarations of the same static data member:

       [class.mem]

       A member shall not be declared twice in the
       member-specification.  */
  else if (TREE_CODE (decl) == VAR_DECL && TREE_CODE (bval) == VAR_DECL
	   && DECL_EXTERNAL (decl) && DECL_EXTERNAL (bval)
	   && !DECL_CLASS_SCOPE_P (decl))
    {
      duplicate_decls (decl, binding->value, /*newdecl_is_friend=*/false);
      ok = false;
    }
  else if (TREE_CODE (decl) == NAMESPACE_DECL
	   && TREE_CODE (bval) == NAMESPACE_DECL
	   && DECL_NAMESPACE_ALIAS (decl)
	   && DECL_NAMESPACE_ALIAS (bval)
	   && ORIGINAL_NAMESPACE (bval) == ORIGINAL_NAMESPACE (decl))
    /* [namespace.alias]

      In a declarative region, a namespace-alias-definition can be
      used to redefine a namespace-alias declared in that declarative
      region to refer only to the namespace to which it already
      refers.  */
    ok = false;
  else
    {
      error ("declaration of %q#D", decl);
      error ("conflicts with previous declaration %q+#D", bval);
      ok = false;
    }

  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, ok);
}