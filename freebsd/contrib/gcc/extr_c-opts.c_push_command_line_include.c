#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct deferred_opt {scalar_t__ code; int /*<<< orphan*/  arg; } ;
struct TYPE_4__ {int /*<<< orphan*/  print_include_names; int /*<<< orphan*/  preprocessed; int /*<<< orphan*/  warn_unused_macros; } ;
struct TYPE_3__ {int /*<<< orphan*/  trace_includes; } ;

/* Variables and functions */
 int /*<<< orphan*/  LC_RENAME ; 
 scalar_t__ OPT_include ; 
 int /*<<< orphan*/  cpp_change_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* cpp_opts ; 
 scalar_t__ cpp_push_include (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ deferred_count ; 
 struct deferred_opt* deferred_opts ; 
 scalar_t__ include_cursor ; 
 TYPE_1__ line_table ; 
 int /*<<< orphan*/  parse_in ; 
 int /*<<< orphan*/  this_input_filename ; 
 int /*<<< orphan*/  warn_unused_macros ; 

__attribute__((used)) static void
push_command_line_include (void)
{
  while (include_cursor < deferred_count)
    {
      struct deferred_opt *opt = &deferred_opts[include_cursor++];

      if (!cpp_opts->preprocessed && opt->code == OPT_include
	  && cpp_push_include (parse_in, opt->arg))
	return;
    }

  if (include_cursor == deferred_count)
    {
      include_cursor++;
      /* -Wunused-macros should only warn about macros defined hereafter.  */
      cpp_opts->warn_unused_macros = warn_unused_macros;
      /* Restore the line map from <command line>.  */
      if (!cpp_opts->preprocessed)
	cpp_change_file (parse_in, LC_RENAME, this_input_filename);

      /* Set this here so the client can change the option if it wishes,
	 and after stacking the main file so we don't trace the main file.  */
      line_table.trace_includes = cpp_opts->print_include_names;
    }
}