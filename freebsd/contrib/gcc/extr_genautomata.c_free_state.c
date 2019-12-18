#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* state_t ;
struct TYPE_4__ {struct TYPE_4__* next_equiv_class_state; int /*<<< orphan*/  component_states; } ;

/* Variables and functions */
 TYPE_1__* first_free_state ; 
 int /*<<< orphan*/  free_alt_states (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_state (state_t state)
{
  free_alt_states (state->component_states);
  state->next_equiv_class_state = first_free_state;
  first_free_state = state;
}