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
typedef  TYPE_2__* automaton_t ;
struct TYPE_9__ {int NDFA_states_num; int NDFA_arcs_num; int DFA_states_num; int DFA_arcs_num; int minimal_DFA_states_num; int minimal_DFA_arcs_num; TYPE_1__* corresponding_automaton_decl; } ;
struct TYPE_8__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDFA_time ; 
 int /*<<< orphan*/  NDFA_to_DFA (TYPE_2__*) ; 
 int /*<<< orphan*/  NDFA_to_DFA_time ; 
 int /*<<< orphan*/  count_states_and_arcs (TYPE_2__*,int*,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  make_automaton (TYPE_2__*) ; 
 int /*<<< orphan*/  minimize_DFA (TYPE_2__*) ; 
 int /*<<< orphan*/  minimize_time ; 
 int /*<<< orphan*/  no_minimization_flag ; 
 scalar_t__ progress_flag ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  ticker_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ticker_on (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
build_automaton (automaton_t automaton)
{
  int states_num;
  int arcs_num;

  ticker_on (&NDFA_time);
  if (progress_flag)
    {
      if (automaton->corresponding_automaton_decl == NULL)
	fprintf (stderr, "Create anonymous automaton");
      else
	fprintf (stderr, "Create automaton `%s'",
		 automaton->corresponding_automaton_decl->name);
      fprintf (stderr, " (1 dot is 100 new states):");
    }
  make_automaton (automaton);
  if (progress_flag)
    fprintf (stderr, " done\n");
  ticker_off (&NDFA_time);
  count_states_and_arcs (automaton, &states_num, &arcs_num);
  automaton->NDFA_states_num = states_num;
  automaton->NDFA_arcs_num = arcs_num;
  ticker_on (&NDFA_to_DFA_time);
  if (progress_flag)
    {
      if (automaton->corresponding_automaton_decl == NULL)
	fprintf (stderr, "Make anonymous DFA");
      else
	fprintf (stderr, "Make DFA `%s'",
		 automaton->corresponding_automaton_decl->name);
      fprintf (stderr, " (1 dot is 100 new states):");
    }
  NDFA_to_DFA (automaton);
  if (progress_flag)
    fprintf (stderr, " done\n");
  ticker_off (&NDFA_to_DFA_time);
  count_states_and_arcs (automaton, &states_num, &arcs_num);
  automaton->DFA_states_num = states_num;
  automaton->DFA_arcs_num = arcs_num;
  if (!no_minimization_flag)
    {
      ticker_on (&minimize_time);
      if (progress_flag)
	{
	  if (automaton->corresponding_automaton_decl == NULL)
	    fprintf (stderr, "Minimize anonymous DFA...");
	  else
	    fprintf (stderr, "Minimize DFA `%s'...",
		     automaton->corresponding_automaton_decl->name);
	}
      minimize_DFA (automaton);
      if (progress_flag)
	fprintf (stderr, "done\n");
      ticker_off (&minimize_time);
      count_states_and_arcs (automaton, &states_num, &arcs_num);
      automaton->minimal_DFA_states_num = states_num;
      automaton->minimal_DFA_arcs_num = arcs_num;
    }
}