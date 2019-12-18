#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* state_t ;
typedef  unsigned int hashval_t ;
typedef  TYPE_4__* alt_state_t ;
struct TYPE_8__ {TYPE_1__* state; struct TYPE_8__* next_sorted_alt_state; } ;
struct TYPE_7__ {TYPE_2__* automaton; TYPE_4__* component_states; int /*<<< orphan*/  reservs; } ;
struct TYPE_6__ {unsigned int automaton_order_num; } ;
struct TYPE_5__ {unsigned int unique_num; } ;

/* Variables and functions */
 int CHAR_BIT ; 
 unsigned int reserv_sets_hash_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
state_hash (const void *state)
{
  unsigned int hash_value;
  alt_state_t alt_state;

  if (((state_t) state)->component_states == NULL)
    hash_value = reserv_sets_hash_value (((state_t) state)->reservs);
  else
    {
      hash_value = 0;
      for (alt_state = ((state_t) state)->component_states;
           alt_state != NULL;
           alt_state = alt_state->next_sorted_alt_state)
        hash_value = (((hash_value >> (sizeof (unsigned) - 1) * CHAR_BIT)
                       | (hash_value << CHAR_BIT))
                      + alt_state->state->unique_num);
    }
  hash_value = (((hash_value >> (sizeof (unsigned) - 1) * CHAR_BIT)
                 | (hash_value << CHAR_BIT))
                + ((state_t) state)->automaton->automaton_order_num);
  return hash_value;
}