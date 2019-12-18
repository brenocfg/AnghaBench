#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t timevar_id_t ;
struct timevar_time_def {int dummy; } ;
struct timevar_stack_def {struct timevar_stack_def* next; TYPE_1__* timevar; } ;
struct TYPE_2__ {int /*<<< orphan*/  elapsed; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  get_time (struct timevar_time_def*) ; 
 struct timevar_stack_def* stack ; 
 struct timevar_time_def start_time ; 
 int /*<<< orphan*/  timevar_accumulate (int /*<<< orphan*/ *,struct timevar_time_def*,struct timevar_time_def*) ; 
 TYPE_1__* timevars ; 
 struct timevar_stack_def* unused_stack_instances ; 

void
timevar_pop_1 (timevar_id_t timevar)
{
  struct timevar_time_def now;
  struct timevar_stack_def *popped = stack;

  gcc_assert (&timevars[timevar] == stack->timevar);
  
  /* What time is it?  */
  get_time (&now);

  /* Attribute the elapsed time to the element we're popping.  */
  timevar_accumulate (&popped->timevar->elapsed, &start_time, &now);

  /* Reset the start time; from now on, time is attributed to the
     element just exposed on the stack.  */
  start_time = now;

  /* Take the item off the stack.  */
  stack = stack->next;

  /* Don't delete the stack element; instead, add it to the list of
     unused elements for later use.  */
  popped->next = unused_stack_instances;
  unused_stack_instances = popped;
}