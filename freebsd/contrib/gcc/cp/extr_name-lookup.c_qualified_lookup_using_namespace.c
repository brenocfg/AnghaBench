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
struct scope_binding {scalar_t__ value; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  cxx_binding ;

/* Variables and functions */
 scalar_t__ DECL_NAMESPACE_USING (scalar_t__) ; 
 int /*<<< orphan*/  NAMESPACE_LEVEL (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ ORIGINAL_NAMESPACE (scalar_t__) ; 
 int /*<<< orphan*/  POP_TIMEVAR_AND_RETURN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_INDIRECT_USING (scalar_t__) ; 
 scalar_t__ TREE_PURPOSE (scalar_t__) ; 
 int /*<<< orphan*/  TV_NAME_LOOKUP ; 
 int /*<<< orphan*/  ambiguous_decl (struct scope_binding*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * cxx_scope_find_binding_for_name (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ is_associated_namespace (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  purpose_member (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 
 scalar_t__ tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool
qualified_lookup_using_namespace (tree name, tree scope,
				  struct scope_binding *result, int flags)
{
  /* Maintain a list of namespaces visited...  */
  tree seen = NULL_TREE;
  /* ... and a list of namespace yet to see.  */
  tree todo = NULL_TREE;
  tree todo_maybe = NULL_TREE;
  tree usings;
  timevar_push (TV_NAME_LOOKUP);
  /* Look through namespace aliases.  */
  scope = ORIGINAL_NAMESPACE (scope);
  while (scope && result->value != error_mark_node)
    {
      cxx_binding *binding =
	cxx_scope_find_binding_for_name (NAMESPACE_LEVEL (scope), name);
      seen = tree_cons (scope, NULL_TREE, seen);
      if (binding)
	/* LLVM LOCAL mainline */
	ambiguous_decl (result, binding, flags);

      /* Consider strong using directives always, and non-strong ones
	 if we haven't found a binding yet.  ??? Shouldn't we consider
	 non-strong ones if the initial RESULT is non-NULL, but the
	 binding in the given namespace is?  */
      for (usings = DECL_NAMESPACE_USING (scope); usings;
	   usings = TREE_CHAIN (usings))
	/* If this was a real directive, and we have not seen it.  */
	if (!TREE_INDIRECT_USING (usings))
	  {
	    /* Try to avoid queuing the same namespace more than once,
	       the exception being when a namespace was already
	       enqueued for todo_maybe and then a strong using is
	       found for it.  We could try to remove it from
	       todo_maybe, but it's probably not worth the effort.  */
	    if (is_associated_namespace (scope, TREE_PURPOSE (usings))
		&& !purpose_member (TREE_PURPOSE (usings), seen)
		&& !purpose_member (TREE_PURPOSE (usings), todo))
	      todo = tree_cons (TREE_PURPOSE (usings), NULL_TREE, todo);
	    else if ((!result->value && !result->type)
		     && !purpose_member (TREE_PURPOSE (usings), seen)
		     && !purpose_member (TREE_PURPOSE (usings), todo)
		     && !purpose_member (TREE_PURPOSE (usings), todo_maybe))
	      todo_maybe = tree_cons (TREE_PURPOSE (usings), NULL_TREE,
				      todo_maybe);
	  }
      if (todo)
	{
	  scope = TREE_PURPOSE (todo);
	  todo = TREE_CHAIN (todo);
	}
      else if (todo_maybe
	       && (!result->value && !result->type))
	{
	  scope = TREE_PURPOSE (todo_maybe);
	  todo = TREE_CHAIN (todo_maybe);
	  todo_maybe = NULL_TREE;
	}
      else
	scope = NULL_TREE; /* If there never was a todo list.  */
    }
  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, result->value != error_mark_node);
}