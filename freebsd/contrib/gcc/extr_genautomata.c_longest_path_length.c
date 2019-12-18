#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* state_t ;
typedef  TYPE_3__* arc_t ;
struct TYPE_11__ {TYPE_2__* to_state; TYPE_1__* insn; } ;
struct TYPE_10__ {int longest_path_length; } ;
struct TYPE_9__ {scalar_t__ insn_reserv_decl; } ;

/* Variables and functions */
 scalar_t__ DECL_INSN_RESERV (int /*<<< orphan*/ ) ; 
 int ON_THE_PATH ; 
 int UNDEFINED_LONGEST_PATH_LENGTH ; 
 int /*<<< orphan*/  advance_cycle_insn_decl ; 
 TYPE_3__* first_out_arc (TYPE_2__*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_3__* next_out_arc (TYPE_3__*) ; 

__attribute__((used)) static int
longest_path_length (state_t state)
{
  arc_t arc;
  int length, result;

  if (state->longest_path_length != UNDEFINED_LONGEST_PATH_LENGTH)
    {
      /* We don't expect the path cycle here.  Our graph may contain
      	 only cycles with one state on the path not containing `cycle
      	 advance' arcs -- see comment below.  */
      gcc_assert (state->longest_path_length != ON_THE_PATH);
      
      /* We already visited the state.  */
      return state->longest_path_length;
    }

  result = 0;
  for (arc = first_out_arc (state); arc != NULL; arc = next_out_arc (arc))
    /* Ignore cycles containing one state and `cycle advance' arcs.  */
    if (arc->to_state != state
	&& (arc->insn->insn_reserv_decl
	    != DECL_INSN_RESERV (advance_cycle_insn_decl)))
    {
      length = longest_path_length (arc->to_state);
      if (length > result)
	result = length;
    }
  state->longest_path_length = result + 1;
  return result;
}