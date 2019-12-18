#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* state_t ;
typedef  int /*<<< orphan*/  reserv_sets_t ;
struct TYPE_8__ {int /*<<< orphan*/  reservs; int /*<<< orphan*/  automaton; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_state (TYPE_1__*) ; 
 TYPE_1__* get_free_state (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* insert_state (TYPE_1__*) ; 
 int /*<<< orphan*/  reserv_sets_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reserv_sets_shift (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static state_t
state_shift (state_t state, reserv_sets_t reservs)
{
  state_t result;
  state_t state_in_table;

  result = get_free_state (1, state->automaton);
  reserv_sets_shift (result->reservs, state->reservs);
  reserv_sets_and (result->reservs, result->reservs, reservs);
  state_in_table = insert_state (result);
  if (result != state_in_table)
    {
      free_state (result);
      result = state_in_table;
    }
  return result;
}