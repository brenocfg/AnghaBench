#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  state_t ;
typedef  TYPE_4__* arc_t ;
struct TYPE_11__ {TYPE_3__* insn; TYPE_1__* to_state; } ;
struct TYPE_10__ {TYPE_2__* insn_reserv_decl; } ;
struct TYPE_9__ {int equiv_class_num; } ;
struct TYPE_8__ {int equiv_class_num_1; int equiv_class_num_2; } ;

/* Variables and functions */
 TYPE_4__* first_out_arc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_4__* next_out_arc (TYPE_4__*) ; 

__attribute__((used)) static void
set_out_arc_insns_equiv_num (state_t state, int odd_iteration_flag)
{
  arc_t arc;

  for (arc = first_out_arc (state); arc != NULL; arc = next_out_arc (arc))
    {
      gcc_assert (!arc->insn->insn_reserv_decl->equiv_class_num);
      arc->insn->insn_reserv_decl->equiv_class_num
	= (odd_iteration_flag
           ? arc->to_state->equiv_class_num_1
	   : arc->to_state->equiv_class_num_2);
      gcc_assert (arc->insn->insn_reserv_decl->equiv_class_num);
    }
}