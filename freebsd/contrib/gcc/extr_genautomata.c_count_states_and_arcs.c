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
typedef  int /*<<< orphan*/  automaton_t ;

/* Variables and functions */
 int curr_counted_arcs_num ; 
 int curr_counted_states_num ; 
 int /*<<< orphan*/  incr_states_and_arcs_nums ; 
 int /*<<< orphan*/  pass_states (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
count_states_and_arcs (automaton_t automaton, int *states_num,
		       int *arcs_num)
{
  curr_counted_states_num = 0;
  curr_counted_arcs_num = 0;
  pass_states (automaton, incr_states_and_arcs_nums);
  *states_num = curr_counted_states_num;
  *arcs_num = curr_counted_arcs_num;
}