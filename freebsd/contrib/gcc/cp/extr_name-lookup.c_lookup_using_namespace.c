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
struct scope_binding {scalar_t__ value; } ;
typedef  int /*<<< orphan*/  cxx_binding ;

/* Variables and functions */
 int /*<<< orphan*/  NAMESPACE_LEVEL (scalar_t__) ; 
 scalar_t__ ORIGINAL_NAMESPACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POP_TIMEVAR_AND_RETURN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_PURPOSE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TV_NAME_LOOKUP ; 
 int /*<<< orphan*/  ambiguous_decl (struct scope_binding*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * cxx_scope_find_binding_for_name (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
lookup_using_namespace (tree name, struct scope_binding *val,
			tree usings, tree scope, int flags)
{
  tree iter;
  timevar_push (TV_NAME_LOOKUP);
  /* Iterate over all used namespaces in current, searching for using
     directives of scope.  */
  for (iter = usings; iter; iter = TREE_CHAIN (iter))
    if (TREE_VALUE (iter) == scope)
      {
	tree used = ORIGINAL_NAMESPACE (TREE_PURPOSE (iter));
	cxx_binding *val1 =
	  cxx_scope_find_binding_for_name (NAMESPACE_LEVEL (used), name);
	/* Resolve ambiguities.  */
	if (val1)
	  /* LLVM LOCAL mainline */
	  ambiguous_decl (val, val1, flags);
      }
  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, val->value != error_mark_node);
}