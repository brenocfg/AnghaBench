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
 int /*<<< orphan*/  check_automaton_usage () ; 
 int /*<<< orphan*/  check_loops_in_regexps () ; 
 int /*<<< orphan*/  check_usage () ; 
 int /*<<< orphan*/  evaluate_max_reserv_cycles () ; 
 int /*<<< orphan*/  have_error ; 
 int /*<<< orphan*/  process_decls () ; 
 int /*<<< orphan*/  process_regexp_decls () ; 

__attribute__((used)) static void
check_all_description (void)
{
  process_decls ();
  check_automaton_usage ();
  process_regexp_decls ();
  check_usage ();
  check_loops_in_regexps ();
  if (!have_error)
    evaluate_max_reserv_cycles ();
}