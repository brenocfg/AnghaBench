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
struct cp_binding_level {struct cp_binding_level* level_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  global_scope_p (struct cp_binding_level*) ; 
 int /*<<< orphan*/  print_binding_level (struct cp_binding_level*) ; 
 int /*<<< orphan*/  stderr ; 

void
print_other_binding_stack (struct cp_binding_level *stack)
{
  struct cp_binding_level *level;
  for (level = stack; !global_scope_p (level); level = level->level_chain)
    {
      fprintf (stderr, "binding level %p\n", (void *) level);
      print_binding_level (level);
    }
}