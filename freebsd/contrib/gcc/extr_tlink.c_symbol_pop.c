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
typedef  int /*<<< orphan*/  symbol ;
struct symbol_stack_entry {struct symbol_stack_entry* next; int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,struct symbol_stack_entry*) ; 
 struct symbol_stack_entry* symbol_stack ; 
 int /*<<< orphan*/  symbol_stack_obstack ; 

__attribute__((used)) static symbol *
symbol_pop (void)
{
  struct symbol_stack_entry *ep = symbol_stack;
  symbol *p;
  if (ep == NULL)
    return NULL;
  p = ep->value;
  symbol_stack = ep->next;
  obstack_free (&symbol_stack_obstack, ep);
  return p;
}