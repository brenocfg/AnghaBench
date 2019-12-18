#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
typedef  TYPE_1__ cxx_binding ;

/* Variables and functions */
 int /*<<< orphan*/  NAMESPACE_LEVEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NULL_TREE ; 
 int /*<<< orphan*/ * ORIGINAL_NAMESPACE (int /*<<< orphan*/ *) ; 
 TYPE_1__* cxx_scope_find_binding_for_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * global_namespace ; 

tree
namespace_binding (tree name, tree scope)
{
  cxx_binding *binding;

  if (scope == NULL)
    scope = global_namespace;
  else
    /* Unnecessary for the global namespace because it can't be an alias. */
    scope = ORIGINAL_NAMESPACE (scope);

  binding = cxx_scope_find_binding_for_name (NAMESPACE_LEVEL (scope), name);

  return binding ? binding->value : NULL_TREE;
}