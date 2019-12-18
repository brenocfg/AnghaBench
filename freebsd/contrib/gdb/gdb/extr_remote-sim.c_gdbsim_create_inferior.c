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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  TARGET_SIGNAL_DEFAULT ; 
 scalar_t__ alloca (int) ; 
 char** buildargv (char*) ; 
 int /*<<< orphan*/  clear_proceed_status () ; 
 scalar_t__ exec_bfd ; 
 int /*<<< orphan*/  gdbsim_desc ; 
 int /*<<< orphan*/  gdbsim_kill () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  init_wait_for_inferior () ; 
 int /*<<< orphan*/  insert_breakpoints () ; 
 int /*<<< orphan*/  make_cleanup_freeargv (char**) ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  printf_filtered (char*,char*,char*) ; 
 int /*<<< orphan*/  proceed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  program_loaded ; 
 int /*<<< orphan*/  remove_breakpoints () ; 
 int /*<<< orphan*/  sim_create_inferior (int /*<<< orphan*/ ,scalar_t__,char**,char**) ; 
 scalar_t__ sr_get_debug () ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void
gdbsim_create_inferior (char *exec_file, char *args, char **env)
{
  int len;
  char *arg_buf, **argv;

  if (exec_file == 0 || exec_bfd == 0)
    warning ("No executable file specified.");
  if (!program_loaded)
    warning ("No program loaded.");

  if (sr_get_debug ())
    printf_filtered ("gdbsim_create_inferior: exec_file \"%s\", args \"%s\"\n",
		     (exec_file ? exec_file : "(NULL)"),
		     args);

  gdbsim_kill ();
  remove_breakpoints ();
  init_wait_for_inferior ();

  if (exec_file != NULL)
    {
      len = strlen (exec_file) + 1 + strlen (args) + 1 + /*slop */ 10;
      arg_buf = (char *) alloca (len);
      arg_buf[0] = '\0';
      strcat (arg_buf, exec_file);
      strcat (arg_buf, " ");
      strcat (arg_buf, args);
      argv = buildargv (arg_buf);
      make_cleanup_freeargv (argv);
    }
  else
    argv = NULL;
  sim_create_inferior (gdbsim_desc, exec_bfd, argv, env);

  inferior_ptid = pid_to_ptid (42);
  insert_breakpoints ();	/* Needed to get correct instruction in cache */

  clear_proceed_status ();

  /* NB: Entry point already set by sim_create_inferior. */
  proceed ((CORE_ADDR) -1, TARGET_SIGNAL_DEFAULT, 0);
}