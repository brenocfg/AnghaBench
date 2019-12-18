#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  NDFA_time ; 
 int /*<<< orphan*/  NDFA_to_DFA_time ; 
 int /*<<< orphan*/  automaton_generation_time ; 
 int /*<<< orphan*/  equiv_time ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  minimize_time ; 
 scalar_t__ ndfa_flag ; 
 int /*<<< orphan*/  output_time ; 
 int /*<<< orphan*/  print_active_time (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transform_time ; 

__attribute__((used)) static void
output_time_statistics (FILE *f)
{
  fprintf (f, "\n  transformation: ");
  print_active_time (f, transform_time);
  fprintf (f, (!ndfa_flag ? ", building DFA: " : ", building NDFA: "));
  print_active_time (f, NDFA_time);
  if (ndfa_flag)
    {
      fprintf (f, ", NDFA -> DFA: ");
      print_active_time (f, NDFA_to_DFA_time);
    }
  fprintf (f, "\n  DFA minimization: ");
  print_active_time (f, minimize_time);
  fprintf (f, ", making insn equivalence: ");
  print_active_time (f, equiv_time);
  fprintf (f, "\n all automaton generation: ");
  print_active_time (f, automaton_generation_time);
  fprintf (f, ", output: ");
  print_active_time (f, output_time);
  fprintf (f, "\n");
}