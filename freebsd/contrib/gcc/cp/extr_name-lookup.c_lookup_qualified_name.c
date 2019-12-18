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
typedef  int /*<<< orphan*/  tree ;
struct scope_binding {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 struct scope_binding EMPTY_SCOPE_BINDING ; 
 int LOOKUP_COMPLAIN ; 
 int LOOKUP_PREFER_TYPES ; 
 scalar_t__ NAMESPACE_DECL ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_mark_node ; 
 scalar_t__ is_aggr_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lookup_member (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ qualified_lookup_using_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scope_binding*,int) ; 

tree
lookup_qualified_name (tree scope, tree name, bool is_type_p, bool complain)
{
  int flags = 0;
  tree t = NULL_TREE;

  if (TREE_CODE (scope) == NAMESPACE_DECL)
    {
      struct scope_binding binding = EMPTY_SCOPE_BINDING;

      flags |= LOOKUP_COMPLAIN;
      if (is_type_p)
	flags |= LOOKUP_PREFER_TYPES;
      if (qualified_lookup_using_namespace (name, scope, &binding, flags))
	t = binding.value;
    }
  else if (is_aggr_type (scope, complain))
    t = lookup_member (scope, name, 2, is_type_p);

  if (!t)
    return error_mark_node;
  return t;
}