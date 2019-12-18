#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* automaton_t ;
typedef  TYPE_2__* ainsn_t ;
struct TYPE_9__ {int insn_equiv_class_num; int first_ainsn_with_given_equivalence_num; struct TYPE_9__* next_equiv_class_insn; struct TYPE_9__* next_same_reservs_insn; scalar_t__ first_insn_with_same_reservs; struct TYPE_9__* next_ainsn; } ;
struct TYPE_8__ {int insn_equiv_classes_num; TYPE_2__* ainsn_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 TYPE_2__* insert_ainsn_into_equiv_class (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  pass_states (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_state_for_insn_equiv_partition ; 

__attribute__((used)) static void
set_insn_equiv_classes (automaton_t automaton)
{
  ainsn_t ainsn;
  ainsn_t first_insn;
  ainsn_t curr_insn;
  ainsn_t cyclic_insn_list;
  ainsn_t insn_with_same_reservs;
  int equiv_classes_num;

  /* All insns are included in one equivalence class.  */
  cyclic_insn_list = NULL;
  for (ainsn = automaton->ainsn_list; ainsn != NULL; ainsn = ainsn->next_ainsn)
    if (ainsn->first_insn_with_same_reservs)
      cyclic_insn_list = insert_ainsn_into_equiv_class (ainsn,
							cyclic_insn_list);
  /* Process insns in order to make equivalence partition.  */
  pass_states (automaton, process_state_for_insn_equiv_partition);
  /* Enumerate equiv classes.  */
  for (ainsn = automaton->ainsn_list; ainsn != NULL; ainsn = ainsn->next_ainsn)
    /* Set undefined value.  */
    ainsn->insn_equiv_class_num = -1;
  equiv_classes_num = 0;
  for (ainsn = automaton->ainsn_list; ainsn != NULL; ainsn = ainsn->next_ainsn)
    if (ainsn->insn_equiv_class_num < 0)
      {
        first_insn = ainsn;
        gcc_assert (first_insn->first_insn_with_same_reservs);
        first_insn->first_ainsn_with_given_equivalence_num = 1;
        curr_insn = first_insn;
        do
          {
            for (insn_with_same_reservs = curr_insn;
                 insn_with_same_reservs != NULL;
                 insn_with_same_reservs
		   = insn_with_same_reservs->next_same_reservs_insn)
              insn_with_same_reservs->insn_equiv_class_num = equiv_classes_num;
            curr_insn = curr_insn->next_equiv_class_insn;
          }
        while (curr_insn != first_insn);
        equiv_classes_num++;
      }
  automaton->insn_equiv_classes_num = equiv_classes_num;
}