#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* state_t ;
typedef  TYPE_2__* alt_state_t ;
struct TYPE_4__ {scalar_t__ state; struct TYPE_4__* next_sorted_alt_state; } ;
struct TYPE_3__ {scalar_t__ automaton; TYPE_2__* component_states; int /*<<< orphan*/  reservs; } ;

/* Variables and functions */
 int reserv_sets_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
state_eq_p (const void *state_1, const void *state_2)
{
  alt_state_t alt_state_1;
  alt_state_t alt_state_2;

  if (((state_t) state_1)->automaton != ((state_t) state_2)->automaton)
    return 0;
  else if (((state_t) state_1)->component_states == NULL
           && ((state_t) state_2)->component_states == NULL)
    return reserv_sets_eq (((state_t) state_1)->reservs,
			   ((state_t) state_2)->reservs);
  else if (((state_t) state_1)->component_states != NULL
           && ((state_t) state_2)->component_states != NULL)
    {
      for (alt_state_1 = ((state_t) state_1)->component_states,
           alt_state_2 = ((state_t) state_2)->component_states;
           alt_state_1 != NULL && alt_state_2 != NULL;
           alt_state_1 = alt_state_1->next_sorted_alt_state,
	   alt_state_2 = alt_state_2->next_sorted_alt_state)
        /* All state in the list must be already in the hash table.
           Also the lists must be sorted.  */
        if (alt_state_1->state != alt_state_2->state)
          return 0;
      return alt_state_1 == alt_state_2;
    }
  else
    return 0;
}