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
struct cp_binding_level {int /*<<< orphan*/  binding_depth; struct cp_binding_level* level_chain; } ;

/* Variables and functions */
 scalar_t__ ENABLE_SCOPE_CHECKING ; 
 int /*<<< orphan*/  binding_depth ; 
 struct cp_binding_level* current_binding_level ; 
 int /*<<< orphan*/  cxx_scope_debug (struct cp_binding_level*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  indent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_line ; 
 scalar_t__ is_class_level ; 
 int keep_next_level_flag ; 

void
push_binding_level (struct cp_binding_level *scope)
{
  /* Add it to the front of currently active scopes stack.  */
  scope->level_chain = current_binding_level;
  current_binding_level = scope;
  keep_next_level_flag = false;

  if (ENABLE_SCOPE_CHECKING)
    {
      scope->binding_depth = binding_depth;
      indent (binding_depth);
      cxx_scope_debug (scope, input_line, "push");
      is_class_level = 0;
      binding_depth++;
    }
}