#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* automaton_t ;
struct TYPE_11__ {int insn_num; } ;
struct TYPE_10__ {TYPE_1__* first_automaton; } ;
struct TYPE_9__ {struct TYPE_9__* next_automaton; } ;

/* Variables and functions */
 char* ADVANCE_CYCLE_VALUE_NAME ; 
 TYPE_8__* DECL_INSN_RESERV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  advance_cycle_insn_decl ; 
 TYPE_7__* description ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  initiate_min_issue_delay_pass_states () ; 
 int /*<<< orphan*/  output_dead_lock_vect (TYPE_1__*) ; 
 int /*<<< orphan*/  output_file ; 
 int /*<<< orphan*/  output_min_issue_delay_table (TYPE_1__*) ; 
 int /*<<< orphan*/  output_reserved_units_table (TYPE_1__*) ; 
 int /*<<< orphan*/  output_trans_table (TYPE_1__*) ; 
 int /*<<< orphan*/  output_translate_vect (TYPE_1__*) ; 

__attribute__((used)) static void
output_tables (void)
{
  automaton_t automaton;

  initiate_min_issue_delay_pass_states ();
  for (automaton = description->first_automaton;
       automaton != NULL;
       automaton = automaton->next_automaton)
    {
      output_translate_vect (automaton);
      output_trans_table (automaton);
      output_min_issue_delay_table (automaton);
      output_dead_lock_vect (automaton);
      output_reserved_units_table (automaton);
    }
  fprintf (output_file, "\n#define %s %d\n\n", ADVANCE_CYCLE_VALUE_NAME,
           DECL_INSN_RESERV (advance_cycle_insn_decl)->insn_num);
}