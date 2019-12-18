#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* alt_state_t ;
struct TYPE_6__ {struct TYPE_6__* next_sorted_alt_state; } ;

/* Variables and functions */
 scalar_t__ alt_state_cmp (TYPE_1__**,TYPE_1__**) ; 

__attribute__((used)) static int
alt_states_eq (alt_state_t alt_states_1, alt_state_t alt_states_2)
{
  while (alt_states_1 != NULL && alt_states_2 != NULL
         && alt_state_cmp (&alt_states_1, &alt_states_2) == 0)
    {
      alt_states_1 = alt_states_1->next_sorted_alt_state;
      alt_states_2 = alt_states_2->next_sorted_alt_state;
    }
  return alt_states_1 == alt_states_2;
}