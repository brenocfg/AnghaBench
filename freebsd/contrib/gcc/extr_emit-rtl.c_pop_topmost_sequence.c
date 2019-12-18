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
struct sequence_stack {int /*<<< orphan*/  last; int /*<<< orphan*/  first; struct sequence_stack* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  first_insn ; 
 int /*<<< orphan*/  last_insn ; 
 struct sequence_stack* seq_stack ; 

void
pop_topmost_sequence (void)
{
  struct sequence_stack *stack, *top = NULL;

  for (stack = seq_stack; stack; stack = stack->next)
    top = stack;

  top->first = first_insn;
  top->last = last_insn;

  end_sequence ();
}