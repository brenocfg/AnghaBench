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
 scalar_t__ NAMESPACE_LEVEL (int /*<<< orphan*/ ) ; 
 struct cp_binding_level* class_binding_level ; 
 struct cp_binding_level* current_binding_level ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  global_namespace ; 
 int /*<<< orphan*/  print_binding_level (scalar_t__) ; 
 int /*<<< orphan*/  print_other_binding_stack (struct cp_binding_level*) ; 
 int /*<<< orphan*/  stderr ; 

void
print_binding_stack (void)
{
  struct cp_binding_level *b;
  fprintf (stderr, "current_binding_level=%p\n"
	   "class_binding_level=%p\n"
	   "NAMESPACE_LEVEL (global_namespace)=%p\n",
	   (void *) current_binding_level, (void *) class_binding_level,
	   (void *) NAMESPACE_LEVEL (global_namespace));
  if (class_binding_level)
    {
      for (b = class_binding_level; b; b = b->level_chain)
	if (b == current_binding_level)
	  break;
      if (b)
	b = class_binding_level;
      else
	b = current_binding_level;
    }
  else
    b = current_binding_level;
  print_other_binding_stack (b);
  fprintf (stderr, "global:\n");
  print_binding_level (NAMESPACE_LEVEL (global_namespace));
}