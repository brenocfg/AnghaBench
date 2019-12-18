#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* arc_t ;
typedef  TYPE_3__* ainsn_t ;
struct TYPE_13__ {TYPE_1__* insn_reserv_decl; struct TYPE_13__* next_equiv_class_insn; } ;
struct TYPE_12__ {scalar_t__ to_state; } ;
struct TYPE_11__ {size_t insn_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_ainsn_from_equiv_class (TYPE_3__*) ; 
 int /*<<< orphan*/  gcc_assert (TYPE_2__*) ; 
 TYPE_3__* insert_ainsn_into_equiv_class (TYPE_3__*,TYPE_3__*) ; 

__attribute__((used)) static void
process_insn_equiv_class (ainsn_t ainsn, arc_t *insn_arcs_array)
{
  ainsn_t next_insn;
  ainsn_t curr_insn;
  ainsn_t cyclic_insn_list;
  arc_t arc;

  gcc_assert (insn_arcs_array [ainsn->insn_reserv_decl->insn_num]);
  curr_insn = ainsn;
  /* New class of ainsns which are not equivalent to given ainsn.  */
  cyclic_insn_list = NULL;
  do
    {
      next_insn = curr_insn->next_equiv_class_insn;
      arc = insn_arcs_array [curr_insn->insn_reserv_decl->insn_num];
      if (arc == NULL
          || (insn_arcs_array [ainsn->insn_reserv_decl->insn_num]->to_state
              != arc->to_state))
        {
          delete_ainsn_from_equiv_class (curr_insn);
          cyclic_insn_list = insert_ainsn_into_equiv_class (curr_insn,
							    cyclic_insn_list);
        }
      curr_insn = next_insn;
    }
  while (curr_insn != ainsn);
}