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
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  chdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_directory ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  execl (char*,char*,char*,...) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 scalar_t__ getenv (char*) ; 
 int safe_strerror (int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 int system (char*) ; 
 int vfork () ; 
 int wait (int*) ; 

__attribute__((used)) static void
shell_escape (char *arg, int from_tty)
{
#ifdef CANT_FORK
  /* If ARG is NULL, they want an inferior shell, but `system' just
     reports if the shell is available when passed a NULL arg.  */
  int rc = system (arg ? arg : "");

  if (!arg)
    arg = "inferior shell";

  if (rc == -1)
    {
      fprintf_unfiltered (gdb_stderr, "Cannot execute %s: %s\n", arg,
			  safe_strerror (errno));
      gdb_flush (gdb_stderr);
    }
  else if (rc)
    {
      fprintf_unfiltered (gdb_stderr, "%s exited with status %d\n", arg, rc);
      gdb_flush (gdb_stderr);
    }
#ifdef GLOBAL_CURDIR
  /* Make sure to return to the directory GDB thinks it is, in case the
     shell command we just ran changed it.  */
  chdir (current_directory);
#endif
#else /* Can fork.  */
  int rc, status, pid;

  if ((pid = vfork ()) == 0)
    {
      char *p, *user_shell;

      if ((user_shell = (char *) getenv ("SHELL")) == NULL)
	user_shell = "/bin/sh";

      /* Get the name of the shell for arg0 */
      if ((p = strrchr (user_shell, '/')) == NULL)
	p = user_shell;
      else
	p++;			/* Get past '/' */

      if (!arg)
	execl (user_shell, p, (char *) 0);
      else
	execl (user_shell, p, "-c", arg, (char *) 0);

      fprintf_unfiltered (gdb_stderr, "Cannot execute %s: %s\n", user_shell,
			  safe_strerror (errno));
      gdb_flush (gdb_stderr);
      _exit (0177);
    }

  if (pid != -1)
    while ((rc = wait (&status)) != pid && rc != -1)
      ;
  else
    error ("Fork failed");
#endif /* Can fork.  */
}