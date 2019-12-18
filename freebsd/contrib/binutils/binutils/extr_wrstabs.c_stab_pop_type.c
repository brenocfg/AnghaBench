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
struct stab_type_stack {char* string; struct stab_type_stack* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct stab_type_stack*) ; 

__attribute__((used)) static char *
stab_pop_type (struct stab_write_handle *info)
{
  struct stab_type_stack *s;
  char *ret;

  s = info->type_stack;
  assert (s != NULL);

  info->type_stack = s->next;

  ret = s->string;

  free (s);

  return ret;
}