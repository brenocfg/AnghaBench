#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct automaton {int dummy; } ;
typedef  TYPE_1__* decl_t ;
typedef  TYPE_2__* automaton_t ;
struct TYPE_15__ {int decls_num; TYPE_2__* first_automaton; TYPE_1__** decls; } ;
struct TYPE_14__ {int automaton_order_num; TYPE_10__* corresponding_automaton_decl; struct TYPE_14__* next_automaton; void* ainsn_list; } ;
struct TYPE_13__ {scalar_t__ mode; } ;
struct TYPE_12__ {char* name; TYPE_2__* corresponding_automaton; scalar_t__ automaton_is_used; } ;

/* Variables and functions */
 TYPE_10__* DECL_AUTOMATON (TYPE_1__*) ; 
 int /*<<< orphan*/  NDFA_time ; 
 int /*<<< orphan*/  NDFA_to_DFA_time ; 
 int automata_num ; 
 int /*<<< orphan*/  build_automaton (TYPE_2__*) ; 
 void* create_ainsns () ; 
 int /*<<< orphan*/  create_alt_states (TYPE_2__*) ; 
 TYPE_2__* create_node (int) ; 
 int /*<<< orphan*/  create_ticker () ; 
 TYPE_6__* description ; 
 scalar_t__ dm_automaton ; 
 int /*<<< orphan*/  enumerate_states (TYPE_2__*) ; 
 int /*<<< orphan*/  equiv_time ; 
 int /*<<< orphan*/  form_ainsn_with_same_reservs (TYPE_2__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  minimize_time ; 
 scalar_t__ progress_flag ; 
 int /*<<< orphan*/  set_insn_equiv_classes (TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  ticker_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ticker_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  units_to_automata_distr () ; 
 int /*<<< orphan*/  units_to_automata_heuristic_distr () ; 

__attribute__((used)) static void
create_automata (void)
{
  automaton_t curr_automaton;
  automaton_t prev_automaton;
  decl_t decl;
  int curr_automaton_num;
  int i;

  if (automata_num != 0)
    {
      units_to_automata_heuristic_distr ();
      for (prev_automaton = NULL, curr_automaton_num = 0;
           curr_automaton_num < automata_num;
           curr_automaton_num++, prev_automaton = curr_automaton)
        {
	  curr_automaton = create_node (sizeof (struct automaton));
	  curr_automaton->ainsn_list = create_ainsns ();
	  curr_automaton->corresponding_automaton_decl = NULL;
	  curr_automaton->next_automaton = NULL;
          curr_automaton->automaton_order_num = curr_automaton_num;
          if (prev_automaton == NULL)
            description->first_automaton = curr_automaton;
          else
            prev_automaton->next_automaton = curr_automaton;
        }
    }
  else
    {
      curr_automaton_num = 0;
      prev_automaton = NULL;
      for (i = 0; i < description->decls_num; i++)
	{
	  decl = description->decls [i];
	  if (decl->mode == dm_automaton
	      && DECL_AUTOMATON (decl)->automaton_is_used)
	    {
	      curr_automaton = create_node (sizeof (struct automaton));
	      curr_automaton->ainsn_list = create_ainsns ();
	      curr_automaton->corresponding_automaton_decl
		= DECL_AUTOMATON (decl);
	      curr_automaton->next_automaton = NULL;
	      DECL_AUTOMATON (decl)->corresponding_automaton = curr_automaton;
	      curr_automaton->automaton_order_num = curr_automaton_num;
	      if (prev_automaton == NULL)
		description->first_automaton = curr_automaton;
	      else
		prev_automaton->next_automaton = curr_automaton;
	      curr_automaton_num++;
	      prev_automaton = curr_automaton;
	    }
	}
      if (curr_automaton_num == 0)
	{
	  curr_automaton = create_node (sizeof (struct automaton));
	  curr_automaton->ainsn_list = create_ainsns ();
	  curr_automaton->corresponding_automaton_decl = NULL;
	  curr_automaton->next_automaton = NULL;
	  description->first_automaton = curr_automaton;
	}
      units_to_automata_distr ();
    }
  NDFA_time = create_ticker ();
  ticker_off (&NDFA_time);
  NDFA_to_DFA_time = create_ticker ();
  ticker_off (&NDFA_to_DFA_time);
  minimize_time = create_ticker ();
  ticker_off (&minimize_time);
  equiv_time = create_ticker ();
  ticker_off (&equiv_time);
  for (curr_automaton = description->first_automaton;
       curr_automaton != NULL;
       curr_automaton = curr_automaton->next_automaton)
    {
      if (progress_flag)
	{
	  if (curr_automaton->corresponding_automaton_decl == NULL)
	    fprintf (stderr, "Prepare anonymous automaton creation ... ");
	  else
	    fprintf (stderr, "Prepare automaton `%s' creation...",
		     curr_automaton->corresponding_automaton_decl->name);
	}
      create_alt_states (curr_automaton);
      form_ainsn_with_same_reservs (curr_automaton);
      if (progress_flag)
	fprintf (stderr, "done\n");
      build_automaton (curr_automaton);
      enumerate_states (curr_automaton);
      ticker_on (&equiv_time);
      set_insn_equiv_classes (curr_automaton);
      ticker_off (&equiv_time);
    }
}