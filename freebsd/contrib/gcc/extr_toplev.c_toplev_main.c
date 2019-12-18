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
 int FATAL_EXIT_CODE ; 
 int SUCCESS_EXIT_CODE ; 
 int /*<<< orphan*/  decode_options (unsigned int,char const**) ; 
 int /*<<< orphan*/  do_compile () ; 
 scalar_t__ errorcount ; 
 int /*<<< orphan*/  exit_after_options ; 
 int /*<<< orphan*/  general_init (char const*) ; 
 int /*<<< orphan*/  randomize () ; 
 char const** save_argv ; 
 scalar_t__ sorrycount ; 

int
toplev_main (unsigned int argc, const char **argv)
{
  save_argv = argv;

  /* Initialization of GCC's environment, and diagnostics.  */
  general_init (argv[0]);

  /* Parse the options and do minimal processing; basically just
     enough to default flags appropriately.  */
  decode_options (argc, argv);

  randomize ();

  /* Exit early if we can (e.g. -help).  */
  if (!exit_after_options)
    do_compile ();

  if (errorcount || sorrycount)
    return (FATAL_EXIT_CODE);

  return (SUCCESS_EXIT_CODE);
}