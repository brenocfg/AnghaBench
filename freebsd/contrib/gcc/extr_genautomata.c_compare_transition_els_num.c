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
typedef  int /*<<< orphan*/  state_t ;

/* Variables and functions */
 int out_state_arcs_num (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_transition_els_num (const void *state_ptr_1,
			    const void *state_ptr_2)
{
  int transition_els_num_1;
  int transition_els_num_2;

  transition_els_num_1 = out_state_arcs_num (*(state_t *) state_ptr_1);
  transition_els_num_2 = out_state_arcs_num (*(state_t *) state_ptr_2);
  if (transition_els_num_1 < transition_els_num_2)
    return 1;
  else if (transition_els_num_1 == transition_els_num_2)
    return 0;
  else
    return -1;
}