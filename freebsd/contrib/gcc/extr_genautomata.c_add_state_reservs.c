#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* state_t ;
typedef  TYPE_2__* alt_state_t ;
struct TYPE_5__ {TYPE_1__* state; struct TYPE_5__* next_sorted_alt_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  reservs; TYPE_2__* component_states; } ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_safe_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap ; 
 int /*<<< orphan*/  reserv_sets_t ; 
 int /*<<< orphan*/  state_reservs ; 

__attribute__((used)) static void
add_state_reservs (state_t state)
{
  alt_state_t curr_alt_state;

  if (state->component_states != NULL)
    for (curr_alt_state = state->component_states;
         curr_alt_state != NULL;
         curr_alt_state = curr_alt_state->next_sorted_alt_state)
      add_state_reservs (curr_alt_state->state);
  else
    VEC_safe_push (reserv_sets_t,heap, state_reservs, state->reservs);
}