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
 int /*<<< orphan*/  TV_TOTAL ; 
 int /*<<< orphan*/  backend_init () ; 
 int /*<<< orphan*/  compile_file () ; 
 int /*<<< orphan*/  errorcount ; 
 int /*<<< orphan*/  finalize () ; 
 scalar_t__ flag_detailed_statistics ; 
 int /*<<< orphan*/  init_adjust_machine_modes () ; 
 scalar_t__ lang_dependent_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_input_filename ; 
 int /*<<< orphan*/  no_backend ; 
 int /*<<< orphan*/  process_options () ; 
 int /*<<< orphan*/  quiet_flag ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ time_report ; 
 int /*<<< orphan*/  timevar_init () ; 
 int /*<<< orphan*/  timevar_print (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_compile (void)
{
  /* Initialize timing first.  The C front ends read the main file in
     the post_options hook, and C++ does file timings.  */
  if (time_report || !quiet_flag  || flag_detailed_statistics)
    timevar_init ();
  timevar_start (TV_TOTAL);

  process_options ();

  /* Don't do any more if an error has already occurred.  */
  if (!errorcount)
    {
      /* This must be run always, because it is needed to compute the FP
	 predefined macros, such as __LDBL_MAX__, for targets using non
	 default FP formats.  */
      init_adjust_machine_modes ();

      /* Set up the back-end if requested.  */
      if (!no_backend)
	backend_init ();

      /* Language-dependent initialization.  Returns true on success.  */
      if (lang_dependent_init (main_input_filename))
	compile_file ();

      finalize ();
    }

  /* Stop timing and print the times.  */
  timevar_stop (TV_TOTAL);
  timevar_print (stderr);
}