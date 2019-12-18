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
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* automaton_t ;
struct TYPE_7__ {int /*<<< orphan*/  full_vect; int /*<<< orphan*/  comb_vect; } ;
struct TYPE_6__ {int insns_num; TYPE_1__* first_automaton; } ;
struct TYPE_5__ {int NDFA_states_num; int NDFA_arcs_num; int DFA_states_num; int DFA_arcs_num; int minimal_DFA_states_num; int minimal_DFA_arcs_num; int insn_equiv_classes_num; int locked_states; TYPE_4__* trans_table; int /*<<< orphan*/  min_issue_delay_table_compression_factor; struct TYPE_5__* next_automaton; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ VEC_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int allocated_alt_states_num ; 
 int allocated_arcs_num ; 
 int allocated_states_num ; 
 scalar_t__ comb_vect_p (TYPE_4__*) ; 
 TYPE_3__* description ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  no_minimization_flag ; 
 int /*<<< orphan*/  output_automaton_name (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  vect_el_t ; 

__attribute__((used)) static void
output_statistics (FILE *f)
{
  automaton_t automaton;
  int states_num;
#ifndef NDEBUG
  int transition_comb_vect_els = 0;
  int transition_full_vect_els = 0;
  int min_issue_delay_vect_els = 0;
  int locked_states = 0;
#endif

  for (automaton = description->first_automaton;
       automaton != NULL;
       automaton = automaton->next_automaton)
    {
      fprintf (f, "\nAutomaton ");
      output_automaton_name (f, automaton);
      fprintf (f, "\n    %5d NDFA states,          %5d NDFA arcs\n",
	       automaton->NDFA_states_num, automaton->NDFA_arcs_num);
      fprintf (f, "    %5d DFA states,           %5d DFA arcs\n",
	       automaton->DFA_states_num, automaton->DFA_arcs_num);
      states_num = automaton->DFA_states_num;
      if (!no_minimization_flag)
	{
	  fprintf (f, "    %5d minimal DFA states,   %5d minimal DFA arcs\n",
		   automaton->minimal_DFA_states_num,
		   automaton->minimal_DFA_arcs_num);
	  states_num = automaton->minimal_DFA_states_num;
	}
      fprintf (f, "    %5d all insns      %5d insn equivalence classes\n",
	       description->insns_num, automaton->insn_equiv_classes_num);
      fprintf (f, "    %d locked states\n", automaton->locked_states);
#ifndef NDEBUG
      fprintf
	(f, "%5ld transition comb vector els, %5ld trans table els: %s\n",
	 (long) VEC_length (vect_el_t, automaton->trans_table->comb_vect),
	 (long) VEC_length (vect_el_t, automaton->trans_table->full_vect),
	 (comb_vect_p (automaton->trans_table)
	  ? "use comb vect" : "use simple vect"));
      fprintf
        (f, "%5ld min delay table els, compression factor %d\n",
         (long) states_num * automaton->insn_equiv_classes_num,
	 automaton->min_issue_delay_table_compression_factor);
      transition_comb_vect_els
	+= VEC_length (vect_el_t, automaton->trans_table->comb_vect);
      transition_full_vect_els
        += VEC_length (vect_el_t, automaton->trans_table->full_vect);
      min_issue_delay_vect_els
	+= states_num * automaton->insn_equiv_classes_num;
      locked_states
	+= automaton->locked_states;
#endif
    }
#ifndef NDEBUG
  fprintf (f, "\n%5d all allocated states,     %5d all allocated arcs\n",
	   allocated_states_num, allocated_arcs_num);
  fprintf (f, "%5d all allocated alternative states\n",
	   allocated_alt_states_num);
  fprintf (f, "%5d all transition comb vector els, %5d all trans table els\n",
	   transition_comb_vect_els, transition_full_vect_els);
  fprintf (f, "%5d all min delay table els\n", min_issue_delay_vect_els);
  fprintf (f, "%5d all locked states\n", locked_states);
#endif
}