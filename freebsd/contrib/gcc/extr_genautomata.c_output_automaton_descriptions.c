#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* automaton_t ;
struct TYPE_7__ {TYPE_1__* first_automaton; } ;
struct TYPE_6__ {struct TYPE_6__* next_automaton; } ;

/* Variables and functions */
 TYPE_5__* description ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  output_automaton_name (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  output_automaton_units (TYPE_1__*) ; 
 int /*<<< orphan*/  output_description_file ; 
 int /*<<< orphan*/  output_state ; 
 int /*<<< orphan*/  pass_states (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
output_automaton_descriptions (void)
{
  automaton_t automaton;

  for (automaton = description->first_automaton;
       automaton != NULL;
       automaton = automaton->next_automaton)
    {
      fprintf (output_description_file, "\nAutomaton ");
      output_automaton_name (output_description_file, automaton);
      fprintf (output_description_file, "\n");
      output_automaton_units (automaton);
      pass_states (automaton, output_state);
    }
}