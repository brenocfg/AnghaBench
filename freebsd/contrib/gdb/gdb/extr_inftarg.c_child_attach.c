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
 int /*<<< orphan*/  attach (int) ; 
 int /*<<< orphan*/  child_ops ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  error_no_arg (char*) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ get_exec_file (int /*<<< orphan*/ ) ; 
 int getpid () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*,...) ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
child_attach (char *args, int from_tty)
{
  if (!args)
    error_no_arg ("process-id to attach");

#ifndef ATTACH_DETACH
  error ("Can't attach to a process on this machine.");
#else
  {
    char *exec_file;
    int pid;
    char *dummy;

    dummy = args;
    pid = strtol (args, &dummy, 0);
    /* Some targets don't set errno on errors, grrr! */
    if ((pid == 0) && (args == dummy))
      error ("Illegal process-id: %s\n", args);

    if (pid == getpid ())	/* Trying to masturbate? */
      error ("I refuse to debug myself!");

    if (from_tty)
      {
	exec_file = (char *) get_exec_file (0);

	if (exec_file)
	  printf_unfiltered ("Attaching to program: %s, %s\n", exec_file,
			     target_pid_to_str (pid_to_ptid (pid)));
	else
	  printf_unfiltered ("Attaching to %s\n",
	                     target_pid_to_str (pid_to_ptid (pid)));

	gdb_flush (gdb_stdout);
      }

    attach (pid);

    inferior_ptid = pid_to_ptid (pid);
    push_target (&child_ops);
  }
#endif /* ATTACH_DETACH */
}