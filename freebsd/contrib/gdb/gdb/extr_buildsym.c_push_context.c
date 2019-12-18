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
struct context_stack {int depth; int /*<<< orphan*/ * name; int /*<<< orphan*/  start_addr; int /*<<< orphan*/  old_blocks; int /*<<< orphan*/ * params; int /*<<< orphan*/ * locals; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct context_stack* context_stack ; 
 int context_stack_depth ; 
 int context_stack_size ; 
 int /*<<< orphan*/ * local_symbols ; 
 int /*<<< orphan*/ * param_symbols ; 
 int /*<<< orphan*/  pending_blocks ; 
 scalar_t__ xrealloc (char*,int) ; 

struct context_stack *
push_context (int desc, CORE_ADDR valu)
{
  struct context_stack *new;

  if (context_stack_depth == context_stack_size)
    {
      context_stack_size *= 2;
      context_stack = (struct context_stack *)
	xrealloc ((char *) context_stack,
		  (context_stack_size * sizeof (struct context_stack)));
    }

  new = &context_stack[context_stack_depth++];
  new->depth = desc;
  new->locals = local_symbols;
  new->params = param_symbols;
  new->old_blocks = pending_blocks;
  new->start_addr = valu;
  new->name = NULL;

  local_symbols = NULL;
  param_symbols = NULL;

  return new;
}