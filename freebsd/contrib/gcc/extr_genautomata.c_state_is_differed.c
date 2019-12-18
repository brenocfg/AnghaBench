#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  TYPE_4__* state_t ;
typedef  TYPE_5__* arc_t ;
struct TYPE_18__ {TYPE_3__* insn; TYPE_1__* to_state; } ;
struct TYPE_17__ {scalar_t__ num_out_arcs; scalar_t__* presence_signature; } ;
struct TYPE_16__ {TYPE_2__* insn_reserv_decl; } ;
struct TYPE_15__ {scalar_t__ equiv_class_num; } ;
struct TYPE_14__ {scalar_t__ equiv_class_num_1; scalar_t__ equiv_class_num_2; } ;
struct TYPE_13__ {int query_units_num; } ;

/* Variables and functions */
 int CHAR_BIT ; 
 TYPE_12__* description ; 
 TYPE_5__* first_out_arc (TYPE_4__*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_5__* next_out_arc (TYPE_5__*) ; 

__attribute__((used)) static int
state_is_differed (state_t state, state_t another_state,
		   int odd_iteration_flag)
{
  arc_t arc;
  unsigned int sz, si;

  gcc_assert (state->num_out_arcs == another_state->num_out_arcs);

  sz = (description->query_units_num + sizeof (int) * CHAR_BIT - 1)
	/ (sizeof (int) * CHAR_BIT);

  for (si = 0; si < sz; si++)
    gcc_assert (state->presence_signature[si]
		== another_state->presence_signature[si]);

  for (arc = first_out_arc (state); arc != NULL; arc = next_out_arc (arc))
    {
      if ((odd_iteration_flag
           ? arc->to_state->equiv_class_num_1
	   : arc->to_state->equiv_class_num_2)
          != arc->insn->insn_reserv_decl->equiv_class_num)
        return 1;
    }

  return 0;
}