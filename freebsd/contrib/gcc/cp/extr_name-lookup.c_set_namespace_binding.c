#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_4__ {scalar_t__ value; } ;
typedef  TYPE_1__ cxx_binding ;

/* Variables and functions */
 int /*<<< orphan*/  NAMESPACE_LEVEL (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ OVERLOAD ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TV_NAME_LOOKUP ; 
 TYPE_1__* binding_for_name (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ global_namespace ; 
 int /*<<< orphan*/  supplement_binding (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

void
set_namespace_binding (tree name, tree scope, tree val)
{
  cxx_binding *b;

  timevar_push (TV_NAME_LOOKUP);
  if (scope == NULL_TREE)
    scope = global_namespace;
  b = binding_for_name (NAMESPACE_LEVEL (scope), name);
  if (!b->value || TREE_CODE (val) == OVERLOAD || val == error_mark_node)
    b->value = val;
  else
    supplement_binding (b, val);
  timevar_pop (TV_NAME_LOOKUP);
}