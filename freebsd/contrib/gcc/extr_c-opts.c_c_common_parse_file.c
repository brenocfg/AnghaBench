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
struct TYPE_2__ {int /*<<< orphan*/  (* end_source_file ) (int /*<<< orphan*/ ) ;scalar_t__ start_end_main_source_file; int /*<<< orphan*/  (* start_source_file ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  c_parse_file () ; 
 int /*<<< orphan*/  cpp_read_main_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpp_undef_all (int /*<<< orphan*/ ) ; 
 TYPE_1__* debug_hooks ; 
 int /*<<< orphan*/  finish_file () ; 
 int /*<<< orphan*/  finish_options () ; 
 int /*<<< orphan*/ * in_fnames ; 
 unsigned int num_in_fnames ; 
 int /*<<< orphan*/  parse_in ; 
 int /*<<< orphan*/  pch_init () ; 
 int /*<<< orphan*/  pop_file_scope () ; 
 int /*<<< orphan*/  push_file_scope () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_input_filename ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 
 int yydebug ; 

void
c_common_parse_file (int set_yydebug)
{
  unsigned int i;

  /* Enable parser debugging, if requested and we can.  If requested
     and we can't, notify the user.  */
#if YYDEBUG != 0
  yydebug = set_yydebug;
#else
  if (set_yydebug)
    warning (0, "YYDEBUG was not defined at build time, -dy ignored");
#endif

  i = 0;
  for (;;)
    {
      /* Start the main input file, if the debug writer wants it. */
      if (debug_hooks->start_end_main_source_file)
	(*debug_hooks->start_source_file) (0, this_input_filename);
      finish_options ();
      pch_init ();
      push_file_scope ();
      c_parse_file ();
      finish_file ();
      pop_file_scope ();
      /* And end the main input file, if the debug writer wants it  */
      if (debug_hooks->start_end_main_source_file)
	(*debug_hooks->end_source_file) (0);
      if (++i >= num_in_fnames)
	break;
      cpp_undef_all (parse_in);
      this_input_filename
	= cpp_read_main_file (parse_in, in_fnames[i]);
      /* If an input file is missing, abandon further compilation.
	 cpplib has issued a diagnostic.  */
      if (!this_input_filename)
	break;
    }
}