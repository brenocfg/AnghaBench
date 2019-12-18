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
 struct symbol_stack_entry* obstack_alloc (int /*<<< orphan*/ *,int) ; 
 struct symbol_stack_entry* symbol_stack ; 
 int /*<<< orphan*/  symbol_stack_obstack ; 

__attribute__((used)) static void
symbol_push (symbol *p)
{
  struct symbol_stack_entry *ep = obstack_alloc
    (&symbol_stack_obstack, sizeof (struct symbol_stack_entry));
  ep->value = p;
  ep->next = symbol_stack;
  symbol_stack = ep;
}