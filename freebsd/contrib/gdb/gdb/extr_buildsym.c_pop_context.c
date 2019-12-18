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
struct context_stack {int dummy; } ;

/* Variables and functions */
 struct context_stack* context_stack ; 
 size_t context_stack_depth ; 
 int /*<<< orphan*/  gdb_assert (int) ; 

struct context_stack *
pop_context (void)
{
  gdb_assert (context_stack_depth > 0);
  return (&context_stack[--context_stack_depth]);
}