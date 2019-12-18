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
struct stab_write_handle {struct stab_type_stack* type_stack; } ;
struct stab_type_stack {long index; unsigned int size; struct stab_type_stack* next; int /*<<< orphan*/ * vtable; int /*<<< orphan*/ * methods; int /*<<< orphan*/ * baseclasses; int /*<<< orphan*/ * fields; int /*<<< orphan*/  definition; int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static bfd_boolean
stab_push_string (struct stab_write_handle *info, const char *string,
		  long index, bfd_boolean definition, unsigned int size)
{
  struct stab_type_stack *s;

  s = (struct stab_type_stack *) xmalloc (sizeof *s);
  s->string = xstrdup (string);
  s->index = index;
  s->definition = definition;
  s->size = size;

  s->fields = NULL;
  s->baseclasses = NULL;
  s->methods = NULL;
  s->vtable = NULL;

  s->next = info->type_stack;
  info->type_stack = s;

  return TRUE;
}