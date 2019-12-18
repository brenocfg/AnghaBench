#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  state_t ;
typedef  TYPE_1__* arc_t ;
struct TYPE_7__ {scalar_t__ first_ainsn_with_given_equivalence_num; } ;
struct TYPE_6__ {TYPE_4__* insn; } ;

/* Variables and functions */
 TYPE_1__* first_out_arc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (TYPE_4__*) ; 
 TYPE_1__* next_out_arc (TYPE_1__*) ; 

__attribute__((used)) static int
out_state_arcs_num (state_t state)
{
  int result;
  arc_t arc;

  result = 0;
  for (arc = first_out_arc (state); arc != NULL; arc = next_out_arc (arc))
    {
      gcc_assert (arc->insn);
      if (arc->insn->first_ainsn_with_given_equivalence_num)
        result++;
    }
  return result;
}