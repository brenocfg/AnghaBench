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
struct parse_stack {struct parse_stack* next; struct parse_stack* prev; } ;

/* Variables and functions */
 struct parse_stack* top_stack ; 
 scalar_t__ xzalloc (int) ; 

__attribute__((used)) static void
push_parse_stack (void)
{
  struct parse_stack *new;

  /* Reuse frames if possible */
  if (top_stack && top_stack->prev)
    new = top_stack->prev;
  else
    new = (struct parse_stack *) xzalloc (sizeof (struct parse_stack));
  /* Initialize new frame with previous content */
  if (top_stack)
    {
      struct parse_stack *prev = new->prev;

      *new = *top_stack;
      top_stack->prev = new;
      new->prev = prev;
      new->next = top_stack;
    }
  top_stack = new;
}