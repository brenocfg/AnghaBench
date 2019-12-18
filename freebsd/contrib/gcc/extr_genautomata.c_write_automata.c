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

/* Variables and functions */
 char* CPU_UNITS_QUERY_MACRO_NAME ; 
 char* DFA_INSN_CODES_LENGTH_VARIABLE_NAME ; 
 char* DFA_INSN_CODES_VARIABLE_NAME ; 
 int /*<<< orphan*/  FATAL_EXIT_CODE ; 
 int /*<<< orphan*/  all_time ; 
 int /*<<< orphan*/  check_time ; 
 int /*<<< orphan*/  create_ticker () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_arcs () ; 
 int /*<<< orphan*/  finish_automata_lists () ; 
 int /*<<< orphan*/  finish_automaton_decl_table () ; 
 int /*<<< orphan*/  finish_decl_table () ; 
 int /*<<< orphan*/  finish_insn_decl_table () ; 
 int /*<<< orphan*/  finish_states () ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  generation_time ; 
 scalar_t__ have_error ; 
 int /*<<< orphan*/  irp ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_automaton_descriptions () ; 
 int /*<<< orphan*/  output_chip_definitions () ; 
 int /*<<< orphan*/  output_cpu_unit_reservation_p () ; 
 int /*<<< orphan*/  output_dead_lock_func () ; 
 int /*<<< orphan*/  output_description () ; 
 int /*<<< orphan*/ * output_description_file ; 
 int /*<<< orphan*/  output_description_file_name ; 
 int /*<<< orphan*/  output_dfa_clean_insn_cache_func () ; 
 int /*<<< orphan*/  output_dfa_finish_func () ; 
 int /*<<< orphan*/  output_dfa_insn_code_func () ; 
 int /*<<< orphan*/  output_dfa_start_func () ; 
 int /*<<< orphan*/  output_file ; 
 int /*<<< orphan*/  output_get_cpu_unit_code_func () ; 
 int /*<<< orphan*/  output_insn_latency_func () ; 
 int /*<<< orphan*/  output_internal_dead_lock_func () ; 
 int /*<<< orphan*/  output_internal_insn_latency_func () ; 
 int /*<<< orphan*/  output_internal_min_issue_delay_func () ; 
 int /*<<< orphan*/  output_internal_reset_func () ; 
 int /*<<< orphan*/  output_internal_trans_func () ; 
 int /*<<< orphan*/  output_max_insn_queue_index_def () ; 
 int /*<<< orphan*/  output_min_insn_conflict_delay_func () ; 
 int /*<<< orphan*/  output_min_issue_delay_func () ; 
 int /*<<< orphan*/  output_print_reservation_func () ; 
 int /*<<< orphan*/  output_reset_func () ; 
 int /*<<< orphan*/  output_size_func () ; 
 int /*<<< orphan*/  output_statistics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_tables () ; 
 int /*<<< orphan*/  output_time ; 
 int /*<<< orphan*/  output_time_statistics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_trans_func () ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_active_time (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ progress_flag ; 
 int /*<<< orphan*/  remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  ticker_off (int /*<<< orphan*/ *) ; 
 scalar_t__ time_flag ; 
 scalar_t__ v_flag ; 

__attribute__((used)) static void
write_automata (void)
{
  output_time = create_ticker ();
  if (progress_flag)
    fprintf (stderr, "Forming and outputting automata tables...");
  output_tables ();
  if (progress_flag)
    {
      fprintf (stderr, "done\n");
      fprintf (stderr, "Output functions to work with automata...");
    }
  output_chip_definitions ();
  output_max_insn_queue_index_def ();
  output_internal_min_issue_delay_func ();
  output_internal_trans_func ();
  /* Cache of insn dfa codes: */
  fprintf (output_file, "\nstatic int *%s;\n", DFA_INSN_CODES_VARIABLE_NAME);
  fprintf (output_file, "\nstatic int %s;\n\n",
	   DFA_INSN_CODES_LENGTH_VARIABLE_NAME);
  output_dfa_insn_code_func ();
  output_trans_func ();
  output_min_issue_delay_func ();
  output_internal_dead_lock_func ();
  output_dead_lock_func ();
  output_size_func ();
  output_internal_reset_func ();
  output_reset_func ();
  output_min_insn_conflict_delay_func ();
  output_internal_insn_latency_func ();
  output_insn_latency_func ();
  output_print_reservation_func ();
  /* Output function get_cpu_unit_code.  */
  fprintf (output_file, "\n#if %s\n\n", CPU_UNITS_QUERY_MACRO_NAME);
  output_get_cpu_unit_code_func ();
  output_cpu_unit_reservation_p ();
  fprintf (output_file, "\n#endif /* #if %s */\n\n",
	   CPU_UNITS_QUERY_MACRO_NAME);
  output_dfa_clean_insn_cache_func ();
  output_dfa_start_func ();
  output_dfa_finish_func ();
  if (progress_flag)
    fprintf (stderr, "done\n");
  if (v_flag)
    {
      output_description_file = fopen (output_description_file_name, "w");
      if (output_description_file == NULL)
	{
	  perror (output_description_file_name);
	  exit (FATAL_EXIT_CODE);
	}
      if (progress_flag)
	fprintf (stderr, "Output automata description...");
      output_description ();
      output_automaton_descriptions ();
      if (progress_flag)
	fprintf (stderr, "done\n");
      output_statistics (output_description_file);
    }
  output_statistics (stderr);
  ticker_off (&output_time);
  output_time_statistics (stderr);
  finish_states ();
  finish_arcs ();
  finish_automata_lists ();
  if (time_flag)
    {
      fprintf (stderr, "Summary:\n");
      fprintf (stderr, "  check time ");
      print_active_time (stderr, check_time);
      fprintf (stderr, ", generation time ");
      print_active_time (stderr, generation_time);
      fprintf (stderr, ", all time ");
      print_active_time (stderr, all_time);
      fprintf (stderr, "\n");
    }
  /* Finish all work.  */
  if (output_description_file != NULL)
    {
      fflush (output_description_file);
      if (ferror (stdout) != 0)
	fatal ("Error in writing DFA description file %s",
               output_description_file_name);
      fclose (output_description_file);
    }
  finish_automaton_decl_table ();
  finish_insn_decl_table ();
  finish_decl_table ();
  obstack_free (&irp, NULL);
  if (have_error && output_description_file != NULL)
    remove (output_description_file_name);
}