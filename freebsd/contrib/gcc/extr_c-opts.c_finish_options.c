#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct deferred_opt {scalar_t__ code; char* arg; } ;
struct TYPE_2__ {int warn_dollars; scalar_t__ directives_only; int /*<<< orphan*/  c99; scalar_t__ pedantic; int /*<<< orphan*/  preprocessed; } ;

/* Variables and functions */
 int /*<<< orphan*/  LC_RENAME ; 
 scalar_t__ OPT_A ; 
 scalar_t__ OPT_D ; 
 scalar_t__ OPT_U ; 
 scalar_t__ OPT_imacros ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  c_cpp_builtins (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb_file_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpp_assert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpp_define (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpp_init_builtins (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpp_init_special_builtins (int /*<<< orphan*/ ) ; 
 TYPE_1__* cpp_opts ; 
 scalar_t__ cpp_push_include (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpp_scan_nooutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpp_unassert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpp_undef (int /*<<< orphan*/ ,char*) ; 
 size_t deferred_count ; 
 struct deferred_opt* deferred_opts ; 
 int /*<<< orphan*/  flag_hosted ; 
 size_t include_cursor ; 
 int /*<<< orphan*/  line_table ; 
 int /*<<< orphan*/  linemap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_in ; 
 int /*<<< orphan*/  push_command_line_include () ; 

__attribute__((used)) static void
finish_options (void)
{
  if (!cpp_opts->preprocessed)
    {
      size_t i;

      cb_file_change (parse_in,
		      linemap_add (&line_table, LC_RENAME, 0,
				   _("<built-in>"), 0));

      cpp_init_builtins (parse_in, flag_hosted);
      c_cpp_builtins (parse_in);

      /* We're about to send user input to cpplib, so make it warn for
	 things that we previously (when we sent it internal definitions)
	 told it to not warn.

	 C99 permits implementation-defined characters in identifiers.
	 The documented meaning of -std= is to turn off extensions that
	 conflict with the specified standard, and since a strictly
	 conforming program cannot contain a '$', we do not condition
	 their acceptance on the -std= setting.  */
      cpp_opts->warn_dollars = (cpp_opts->pedantic && !cpp_opts->c99);

      cb_file_change (parse_in,
		      linemap_add (&line_table, LC_RENAME, 0,
				   _("<command-line>"), 0));

      for (i = 0; i < deferred_count; i++)
	{
	  struct deferred_opt *opt = &deferred_opts[i];

	  if (opt->code == OPT_D)
	    cpp_define (parse_in, opt->arg);
	  else if (opt->code == OPT_U)
	    cpp_undef (parse_in, opt->arg);
	  else if (opt->code == OPT_A)
	    {
	      if (opt->arg[0] == '-')
		cpp_unassert (parse_in, opt->arg + 1);
	      else
		cpp_assert (parse_in, opt->arg);
	    }
	}

      /* Handle -imacros after -D and -U.  */
      for (i = 0; i < deferred_count; i++)
	{
	  struct deferred_opt *opt = &deferred_opts[i];

	  if (opt->code == OPT_imacros
	      && cpp_push_include (parse_in, opt->arg))
	    {
	      /* Disable push_command_line_include callback for now.  */
	      include_cursor = deferred_count + 1;
	      cpp_scan_nooutput (parse_in);
	    }
	}
    }
  else if (cpp_opts->directives_only)
    cpp_init_special_builtins (parse_in);

  include_cursor = 0;
  push_command_line_include ();
}