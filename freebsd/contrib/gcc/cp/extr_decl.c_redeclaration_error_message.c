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
 scalar_t__ COMPLETE_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CP_DECL_THREADPRIVATE_P (scalar_t__) ; 
 scalar_t__ DECL_ANON_UNION_VAR_P (scalar_t__) ; 
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ DECL_EXTERNAL (scalar_t__) ; 
 scalar_t__ DECL_INITIAL (scalar_t__) ; 
 scalar_t__ DECL_LANG_SPECIFIC (scalar_t__) ; 
 scalar_t__ DECL_NAME (scalar_t__) ; 
 scalar_t__ DECL_NAMESPACE_SCOPE_P (scalar_t__) ; 
 scalar_t__ DECL_PURE_VIRTUAL_P (scalar_t__) ; 
 scalar_t__ DECL_TEMPLATE_INFO (scalar_t__) ; 
 scalar_t__ DECL_TEMPLATE_RESULT (scalar_t__) ; 
 scalar_t__ DECL_THREAD_LOCAL_P (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  decls_match (scalar_t__,scalar_t__) ; 
 scalar_t__ same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ template_for_substitution (scalar_t__) ; 
 scalar_t__ toplevel_bindings_p () ; 

__attribute__((used)) static const char *
redeclaration_error_message (tree newdecl, tree olddecl)
{
  if (TREE_CODE (newdecl) == TYPE_DECL)
    {
      /* Because C++ can put things into name space for free,
	 constructs like "typedef struct foo { ... } foo"
	 would look like an erroneous redeclaration.  */
      if (same_type_p (TREE_TYPE (newdecl), TREE_TYPE (olddecl)))
	return NULL;
      else
	return "redefinition of %q#D";
    }
  else if (TREE_CODE (newdecl) == FUNCTION_DECL)
    {
      /* If this is a pure function, its olddecl will actually be
	 the original initialization to `0' (which we force to call
	 abort()).  Don't complain about redefinition in this case.  */
      if (DECL_LANG_SPECIFIC (olddecl) && DECL_PURE_VIRTUAL_P (olddecl)
	  && DECL_INITIAL (olddecl) == NULL_TREE)
	return NULL;

      /* If both functions come from different namespaces, this is not
	 a redeclaration - this is a conflict with a used function.  */
      if (DECL_NAMESPACE_SCOPE_P (olddecl)
	  && DECL_CONTEXT (olddecl) != DECL_CONTEXT (newdecl)
	  && ! decls_match (olddecl, newdecl))
	return "%qD conflicts with used function";

      /* We'll complain about linkage mismatches in
	 warn_extern_redeclared_static.  */

      /* Defining the same name twice is no good.  */
      if (DECL_INITIAL (olddecl) != NULL_TREE
	  && DECL_INITIAL (newdecl) != NULL_TREE)
	{
	  if (DECL_NAME (olddecl) == NULL_TREE)
	    return "%q#D not declared in class";
	  else
	    return "redefinition of %q#D";
	}
      return NULL;
    }
  else if (TREE_CODE (newdecl) == TEMPLATE_DECL)
    {
      tree nt, ot;

      if (TREE_CODE (DECL_TEMPLATE_RESULT (newdecl)) == TYPE_DECL)
	{
	  if (COMPLETE_TYPE_P (TREE_TYPE (newdecl))
	      && COMPLETE_TYPE_P (TREE_TYPE (olddecl)))
	    return "redefinition of %q#D";
	  return NULL;
	}

      if (TREE_CODE (DECL_TEMPLATE_RESULT (newdecl)) != FUNCTION_DECL
	  || (DECL_TEMPLATE_RESULT (newdecl)
	      == DECL_TEMPLATE_RESULT (olddecl)))
	return NULL;

      nt = DECL_TEMPLATE_RESULT (newdecl);
      if (DECL_TEMPLATE_INFO (nt))
	nt = DECL_TEMPLATE_RESULT (template_for_substitution (nt));
      ot = DECL_TEMPLATE_RESULT (olddecl);
      if (DECL_TEMPLATE_INFO (ot))
	ot = DECL_TEMPLATE_RESULT (template_for_substitution (ot));
      if (DECL_INITIAL (nt) && DECL_INITIAL (ot))
	return "redefinition of %q#D";

      return NULL;
    }
  else if (TREE_CODE (newdecl) == VAR_DECL
	   && DECL_THREAD_LOCAL_P (newdecl) != DECL_THREAD_LOCAL_P (olddecl)
	   && (! DECL_LANG_SPECIFIC (olddecl)
	       || ! CP_DECL_THREADPRIVATE_P (olddecl)
	       || DECL_THREAD_LOCAL_P (newdecl)))
    {
      /* Only variables can be thread-local, and all declarations must
	 agree on this property.  */
      if (DECL_THREAD_LOCAL_P (newdecl))
	return "thread-local declaration of %q#D follows "
	       "non-thread-local declaration";
      else
	return "non-thread-local declaration of %q#D follows "
	       "thread-local declaration";
    }
  else if (toplevel_bindings_p () || DECL_NAMESPACE_SCOPE_P (newdecl))
    {
      /* The objects have been declared at namespace scope.  If either
	 is a member of an anonymous union, then this is an invalid
	 redeclaration.  For example:

	   int i;
	   union { int i; };

	   is invalid.  */
      if (DECL_ANON_UNION_VAR_P (newdecl)
	  || DECL_ANON_UNION_VAR_P (olddecl))
	return "redeclaration of %q#D";
      /* If at least one declaration is a reference, there is no
	 conflict.  For example:

	   int i = 3;
	   extern int i;

	 is valid.  */
      if (DECL_EXTERNAL (newdecl) || DECL_EXTERNAL (olddecl))
	return NULL;
      /* Reject two definitions.  */
      return "redefinition of %q#D";
    }
  else
    {
      /* Objects declared with block scope:  */
      /* Reject two definitions, and reject a definition
	 together with an external reference.  */
      if (!(DECL_EXTERNAL (newdecl) && DECL_EXTERNAL (olddecl)))
	return "redeclaration of %q#D";
      return NULL;
    }
}