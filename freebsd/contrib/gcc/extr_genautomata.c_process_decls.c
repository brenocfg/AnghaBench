#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_28__ ;
typedef  struct TYPE_38__   TYPE_26__ ;
typedef  struct TYPE_37__   TYPE_22__ ;
typedef  struct TYPE_36__   TYPE_1__ ;
typedef  struct TYPE_35__   TYPE_18__ ;
typedef  struct TYPE_34__   TYPE_16__ ;
typedef  struct TYPE_33__   TYPE_14__ ;
typedef  struct TYPE_32__   TYPE_13__ ;
typedef  struct TYPE_31__   TYPE_11__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unit_set_el_t ;
struct bypass_decl {scalar_t__ latency; } ;
typedef  int /*<<< orphan*/  pattern_set_el_t ;
typedef  TYPE_1__* decl_t ;
struct TYPE_39__ {int /*<<< orphan*/  final_p; int /*<<< orphan*/  patterns_num; int /*<<< orphan*/  patterns; int /*<<< orphan*/  names_num; int /*<<< orphan*/  names; } ;
struct TYPE_38__ {int automaton_is_used; int /*<<< orphan*/  name; } ;
struct TYPE_37__ {size_t first_list_length; size_t all_names_num; int /*<<< orphan*/ * names; } ;
struct TYPE_36__ {scalar_t__ mode; int /*<<< orphan*/  pos; } ;
struct TYPE_35__ {int /*<<< orphan*/  final_p; int /*<<< orphan*/  patterns_num; int /*<<< orphan*/  patterns; int /*<<< orphan*/  names_num; int /*<<< orphan*/  names; } ;
struct TYPE_34__ {int /*<<< orphan*/  name; } ;
struct TYPE_33__ {int /*<<< orphan*/  name; int /*<<< orphan*/  unit_num; TYPE_26__* automaton_decl; int /*<<< orphan*/ * automaton_name; } ;
struct TYPE_32__ {int decls_num; TYPE_1__** decls; int /*<<< orphan*/  units_num; int /*<<< orphan*/  insns_num; } ;
struct TYPE_31__ {scalar_t__ default_latency; TYPE_10__* bypass_list; int /*<<< orphan*/  name; int /*<<< orphan*/  insn_num; } ;
struct TYPE_30__ {scalar_t__ latency; char* out_insn_name; char* in_insn_name; struct TYPE_30__* next; TYPE_11__* in_insn_reserv; TYPE_11__* out_insn_reserv; } ;

/* Variables and functions */
 TYPE_28__* DECL_ABSENCE (TYPE_1__*) ; 
 TYPE_26__* DECL_AUTOMATON (TYPE_1__*) ; 
 TYPE_10__* DECL_BYPASS (TYPE_1__*) ; 
 TYPE_22__* DECL_EXCL (TYPE_1__*) ; 
 TYPE_11__* DECL_INSN_RESERV (TYPE_1__*) ; 
 TYPE_18__* DECL_PRESENCE (TYPE_1__*) ; 
 TYPE_16__* DECL_RESERV (TYPE_1__*) ; 
 TYPE_14__* DECL_UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NOTHING_NAME ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  add_excls (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_presence_absence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_13__* description ; 
 scalar_t__ dm_absence ; 
 scalar_t__ dm_automaton ; 
 scalar_t__ dm_bypass ; 
 scalar_t__ dm_excl ; 
 scalar_t__ dm_insn_reserv ; 
 scalar_t__ dm_presence ; 
 scalar_t__ dm_reserv ; 
 scalar_t__ dm_unit ; 
 int /*<<< orphan*/  error (char*,char*,...) ; 
 TYPE_1__* find_automaton_decl (int /*<<< orphan*/ *) ; 
 struct bypass_decl* find_bypass (TYPE_10__*,TYPE_11__*) ; 
 TYPE_1__* find_decl (int /*<<< orphan*/ ) ; 
 TYPE_1__* find_insn_decl (char*) ; 
 TYPE_1__* insert_automaton_decl (TYPE_1__*) ; 
 TYPE_1__* insert_decl (TYPE_1__*) ; 
 TYPE_1__* insert_insn_decl (TYPE_1__*) ; 
 int /*<<< orphan*/  process_excls (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_presence_absence_names (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_presence_absence_patterns (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_flag ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,char*,...) ; 

__attribute__((used)) static void
process_decls (void)
{
  decl_t decl;
  decl_t automaton_decl;
  decl_t decl_in_table;
  decl_t out_insn_reserv;
  decl_t in_insn_reserv;
  struct bypass_decl *bypass;
  int automaton_presence;
  int i;

  /* Checking repeated automata declarations.  */
  automaton_presence = 0;
  for (i = 0; i < description->decls_num; i++)
    {
      decl = description->decls [i];
      if (decl->mode == dm_automaton)
	{
	  automaton_presence = 1;
	  decl_in_table = insert_automaton_decl (decl);
	  if (decl_in_table != decl)
	    {
	      if (!w_flag)
		error ("repeated declaration of automaton `%s'",
		       DECL_AUTOMATON (decl)->name);
	      else
		warning (0, "repeated declaration of automaton `%s'",
			 DECL_AUTOMATON (decl)->name);
	    }
	}
    }
  /* Checking undeclared automata, repeated declarations (except for
     automata) and correctness of their attributes (insn latency times
     etc.).  */
  for (i = 0; i < description->decls_num; i++)
    {
      decl = description->decls [i];
      if (decl->mode == dm_insn_reserv)
	{
	  if (DECL_INSN_RESERV (decl)->default_latency < 0)
	    error ("define_insn_reservation `%s' has negative latency time",
		   DECL_INSN_RESERV (decl)->name);
	  DECL_INSN_RESERV (decl)->insn_num = description->insns_num;
	  description->insns_num++;
	  decl_in_table = insert_insn_decl (decl);
	  if (decl_in_table != decl)
	    error ("`%s' is already used as insn reservation name",
		   DECL_INSN_RESERV (decl)->name);
	}
      else if (decl->mode == dm_bypass)
	{
	  if (DECL_BYPASS (decl)->latency < 0)
	    error ("define_bypass `%s - %s' has negative latency time",
		   DECL_BYPASS (decl)->out_insn_name,
		   DECL_BYPASS (decl)->in_insn_name);
	}
      else if (decl->mode == dm_unit || decl->mode == dm_reserv)
	{
	  if (decl->mode == dm_unit)
	    {
	      DECL_UNIT (decl)->automaton_decl = NULL;
	      if (DECL_UNIT (decl)->automaton_name != NULL)
		{
		  automaton_decl
                    = find_automaton_decl (DECL_UNIT (decl)->automaton_name);
		  if (automaton_decl == NULL)
		    error ("automaton `%s' is not declared",
			   DECL_UNIT (decl)->automaton_name);
		  else
		    {
		      DECL_AUTOMATON (automaton_decl)->automaton_is_used = 1;
		      DECL_UNIT (decl)->automaton_decl
			= DECL_AUTOMATON (automaton_decl);
		    }
		}
	      else if (automaton_presence)
		error ("define_unit `%s' without automaton when one defined",
		       DECL_UNIT (decl)->name);
	      DECL_UNIT (decl)->unit_num = description->units_num;
	      description->units_num++;
	      if (strcmp (DECL_UNIT (decl)->name, NOTHING_NAME) == 0)
		{
		  error ("`%s' is declared as cpu unit", NOTHING_NAME);
		  continue;
		}
	      decl_in_table = find_decl (DECL_UNIT (decl)->name);
	    }
	  else
	    {
	      if (strcmp (DECL_RESERV (decl)->name, NOTHING_NAME) == 0)
		{
		  error ("`%s' is declared as cpu reservation", NOTHING_NAME);
		  continue;
		}
	      decl_in_table = find_decl (DECL_RESERV (decl)->name);
	    }
	  if (decl_in_table == NULL)
	    decl_in_table = insert_decl (decl);
	  else
	    {
	      if (decl->mode == dm_unit)
		error ("repeated declaration of unit `%s'",
		       DECL_UNIT (decl)->name);
	      else
		error ("repeated declaration of reservation `%s'",
		       DECL_RESERV (decl)->name);
	    }
	}
    }
  /* Check bypasses and form list of bypasses for each (output)
     insn.  */
  for (i = 0; i < description->decls_num; i++)
    {
      decl = description->decls [i];
      if (decl->mode == dm_bypass)
	{
	  out_insn_reserv = find_insn_decl (DECL_BYPASS (decl)->out_insn_name);
	  in_insn_reserv = find_insn_decl (DECL_BYPASS (decl)->in_insn_name);
	  if (out_insn_reserv == NULL)
	    error ("there is no insn reservation `%s'",
		   DECL_BYPASS (decl)->out_insn_name);
	  else if (in_insn_reserv == NULL)
	    error ("there is no insn reservation `%s'",
		   DECL_BYPASS (decl)->in_insn_name);
	  else
	    {
	      DECL_BYPASS (decl)->out_insn_reserv
		= DECL_INSN_RESERV (out_insn_reserv);
	      DECL_BYPASS (decl)->in_insn_reserv
		= DECL_INSN_RESERV (in_insn_reserv);
	      bypass
		= find_bypass (DECL_INSN_RESERV (out_insn_reserv)->bypass_list,
			       DECL_BYPASS (decl)->in_insn_reserv);
	      if (bypass != NULL)
		{
		  if (DECL_BYPASS (decl)->latency == bypass->latency)
		    {
		      if (!w_flag)
			error
			  ("the same bypass `%s - %s' is already defined",
			   DECL_BYPASS (decl)->out_insn_name,
			   DECL_BYPASS (decl)->in_insn_name);
		      else
			warning
			  (0, "the same bypass `%s - %s' is already defined",
			   DECL_BYPASS (decl)->out_insn_name,
			   DECL_BYPASS (decl)->in_insn_name);
		    }
		  else
		    error ("bypass `%s - %s' is already defined",
			   DECL_BYPASS (decl)->out_insn_name,
			   DECL_BYPASS (decl)->in_insn_name);
		}
	      else
		{
		  DECL_BYPASS (decl)->next
		    = DECL_INSN_RESERV (out_insn_reserv)->bypass_list;
		  DECL_INSN_RESERV (out_insn_reserv)->bypass_list
		    = DECL_BYPASS (decl);
		}
	    }
	}
    }

  /* Check exclusion set declarations and form exclusion sets.  */
  for (i = 0; i < description->decls_num; i++)
    {
      decl = description->decls [i];
      if (decl->mode == dm_excl)
	{
	  unit_set_el_t unit_set_el_list;
	  unit_set_el_t unit_set_el_list_2;

	  unit_set_el_list
            = process_excls (DECL_EXCL (decl)->names,
			     DECL_EXCL (decl)->first_list_length, decl->pos);
	  unit_set_el_list_2
	    = process_excls (&DECL_EXCL (decl)->names
			     [DECL_EXCL (decl)->first_list_length],
                             DECL_EXCL (decl)->all_names_num
                             - DECL_EXCL (decl)->first_list_length,
                             decl->pos);
	  add_excls (unit_set_el_list, unit_set_el_list_2, decl->pos);
	  add_excls (unit_set_el_list_2, unit_set_el_list, decl->pos);
	}
    }

  /* Check presence set declarations and form presence sets.  */
  for (i = 0; i < description->decls_num; i++)
    {
      decl = description->decls [i];
      if (decl->mode == dm_presence)
	{
	  unit_set_el_t unit_set_el_list;
	  pattern_set_el_t pattern_set_el_list;

	  unit_set_el_list
            = process_presence_absence_names
	      (DECL_PRESENCE (decl)->names, DECL_PRESENCE (decl)->names_num,
	       decl->pos, TRUE, DECL_PRESENCE (decl)->final_p);
	  pattern_set_el_list
	    = process_presence_absence_patterns
	      (DECL_PRESENCE (decl)->patterns,
	       DECL_PRESENCE (decl)->patterns_num,
	       decl->pos, TRUE, DECL_PRESENCE (decl)->final_p);
	  add_presence_absence (unit_set_el_list, pattern_set_el_list,
				decl->pos, TRUE,
				DECL_PRESENCE (decl)->final_p);
	}
    }

  /* Check absence set declarations and form absence sets.  */
  for (i = 0; i < description->decls_num; i++)
    {
      decl = description->decls [i];
      if (decl->mode == dm_absence)
	{
	  unit_set_el_t unit_set_el_list;
	  pattern_set_el_t pattern_set_el_list;

	  unit_set_el_list
            = process_presence_absence_names
	      (DECL_ABSENCE (decl)->names, DECL_ABSENCE (decl)->names_num,
	       decl->pos, FALSE, DECL_ABSENCE (decl)->final_p);
	  pattern_set_el_list
	    = process_presence_absence_patterns
	      (DECL_ABSENCE (decl)->patterns,
	       DECL_ABSENCE (decl)->patterns_num,
	       decl->pos, FALSE, DECL_ABSENCE (decl)->final_p);
	  add_presence_absence (unit_set_el_list, pattern_set_el_list,
				decl->pos, FALSE,
				DECL_ABSENCE (decl)->final_p);
	}
    }
}