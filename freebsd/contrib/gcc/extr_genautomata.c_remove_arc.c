#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* state_t ;
typedef  TYPE_2__* arc_t ;
struct TYPE_8__ {struct TYPE_8__* next_out_arc; } ;
struct TYPE_7__ {int /*<<< orphan*/  num_out_arcs; TYPE_2__* first_out_arc; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_arc (TYPE_2__*) ; 
 int /*<<< orphan*/  gcc_assert (TYPE_2__*) ; 

__attribute__((used)) static void
remove_arc (state_t from_state, arc_t arc)
{
  arc_t prev_arc;
  arc_t curr_arc;

  gcc_assert (arc);
  for (prev_arc = NULL, curr_arc = from_state->first_out_arc;
       curr_arc != NULL;
       prev_arc = curr_arc, curr_arc = curr_arc->next_out_arc)
    if (curr_arc == arc)
      break;
  gcc_assert (curr_arc);
  if (prev_arc == NULL)
    from_state->first_out_arc = arc->next_out_arc;
  else
    prev_arc->next_out_arc = arc->next_out_arc;
  from_state->num_out_arcs--;
  free_arc (arc);
}