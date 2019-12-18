#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* state_t ;
typedef  int /*<<< orphan*/  reserv_sets_t ;
struct TYPE_9__ {scalar_t__ automaton; int /*<<< orphan*/  reservs; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_state (TYPE_1__*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__* get_free_state (int,scalar_t__) ; 
 TYPE_1__* insert_state (TYPE_1__*) ; 
 int /*<<< orphan*/  reserv_sets_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reserv_sets_or (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static state_t
states_union (state_t state1, state_t state2, reserv_sets_t reservs)
{
  state_t result;
  state_t state_in_table;

  gcc_assert (state1->automaton == state2->automaton);
  result = get_free_state (1, state1->automaton);
  reserv_sets_or (result->reservs, state1->reservs, state2->reservs);
  reserv_sets_and (result->reservs, result->reservs, reservs);
  state_in_table = insert_state (result);
  if (result != state_in_table)
    {
      free_state (result);
      result = state_in_table;
    }
  return result;
}