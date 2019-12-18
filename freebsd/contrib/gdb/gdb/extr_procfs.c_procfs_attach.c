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
 int atoi (char*) ; 
 int /*<<< orphan*/  do_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error_no_arg (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* get_exec_file (int /*<<< orphan*/ ) ; 
 int getpid () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  printf_filtered (char*,char*,...) ; 
 int /*<<< orphan*/  procfs_ops ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
procfs_attach (char *args, int from_tty)
{
  char *exec_file;
  int   pid;

  if (!args)
    error_no_arg ("process-id to attach");

  pid = atoi (args);
  if (pid == getpid ())
    error ("Attaching GDB to itself is not a good idea...");

  if (from_tty)
    {
      exec_file = get_exec_file (0);

      if (exec_file)
	printf_filtered ("Attaching to program `%s', %s\n",
			 exec_file, target_pid_to_str (pid_to_ptid (pid)));
      else
	printf_filtered ("Attaching to %s\n",
	                 target_pid_to_str (pid_to_ptid (pid)));

      fflush (stdout);
    }
  inferior_ptid = do_attach (pid_to_ptid (pid));
  push_target (&procfs_ops);
}