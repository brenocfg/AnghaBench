#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ kind; } ;

/* Variables and functions */
 scalar_t__ ENABLE_SCOPE_CHECKING ; 
 TYPE_1__* current_binding_level ; 
 int /*<<< orphan*/  pop_nested_class () ; 
 int /*<<< orphan*/  poplevel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sk_class ; 
 int /*<<< orphan*/  toplevel_bindings_p () ; 
 int /*<<< orphan*/  verbatim (char*) ; 

void
pop_everything (void)
{
  if (ENABLE_SCOPE_CHECKING)
    verbatim ("XXX entering pop_everything ()\n");
  while (!toplevel_bindings_p ())
    {
      if (current_binding_level->kind == sk_class)
	pop_nested_class ();
      else
	poplevel (0, 0, 0);
    }
  if (ENABLE_SCOPE_CHECKING)
    verbatim ("XXX leaving pop_everything ()\n");
}