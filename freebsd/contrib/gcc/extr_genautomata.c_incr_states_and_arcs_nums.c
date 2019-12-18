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
typedef  int /*<<< orphan*/ * arc_t ;

/* Variables and functions */
 int /*<<< orphan*/  curr_counted_arcs_num ; 
 int /*<<< orphan*/  curr_counted_states_num ; 
 int /*<<< orphan*/ * first_out_arc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * next_out_arc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
incr_states_and_arcs_nums (state_t state)
{
  arc_t arc;

  curr_counted_states_num++;
  for (arc = first_out_arc (state); arc != NULL; arc = next_out_arc (arc))
    curr_counted_arcs_num++;
}