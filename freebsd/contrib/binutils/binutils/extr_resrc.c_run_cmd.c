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
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int PEXECUTE_ONE ; 
 int PEXECUTE_SEARCH ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 char** alloca (int) ; 
 char* choose_temp_base () ; 
 int /*<<< orphan*/  close (int) ; 
 int dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int open (char const*,int,int) ; 
 int pexecute (char const*,char* const*,int /*<<< orphan*/ ,char*,char**,char**,int) ; 
 int /*<<< orphan*/  program_name ; 
 int pwait (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
run_cmd (char *cmd, const char *redir)
{
  char *s;
  int pid, wait_status, retcode;
  int i;
  const char **argv;
  char *errmsg_fmt, *errmsg_arg;
  char *temp_base = choose_temp_base ();
  int in_quote;
  char sep;
  int redir_handle = -1;
  int stdout_save = -1;

  /* Count the args.  */
  i = 0;

  for (s = cmd; *s; s++)
    if (*s == ' ')
      i++;

  i++;
  argv = alloca (sizeof (char *) * (i + 3));
  i = 0;
  s = cmd;

  while (1)
    {
      while (*s == ' ' && *s != 0)
	s++;

      if (*s == 0)
	break;

      in_quote = (*s == '\'' || *s == '"');
      sep = (in_quote) ? *s++ : ' ';
      argv[i++] = s;

      while (*s != sep && *s != 0)
	s++;

      if (*s == 0)
	break;

      *s++ = 0;

      if (in_quote)
	s++;
    }
  argv[i++] = NULL;

  /* Setup the redirection.  We can't use the usual fork/exec and redirect
     since we may be running on non-POSIX Windows host.  */

  fflush (stdout);
  fflush (stderr);

  /* Open temporary output file.  */
  redir_handle = open (redir, O_WRONLY | O_TRUNC | O_CREAT, 0666);
  if (redir_handle == -1)
    fatal (_("can't open temporary file `%s': %s"), redir,
	   strerror (errno));

  /* Duplicate the stdout file handle so it can be restored later.  */
  stdout_save = dup (STDOUT_FILENO);
  if (stdout_save == -1)
    fatal (_("can't redirect stdout: `%s': %s"), redir, strerror (errno));

  /* Redirect stdout to our output file.  */
  dup2 (redir_handle, STDOUT_FILENO);

  pid = pexecute (argv[0], (char * const *) argv, program_name, temp_base,
		  &errmsg_fmt, &errmsg_arg, PEXECUTE_ONE | PEXECUTE_SEARCH);

  /* Restore stdout to its previous setting.  */
  dup2 (stdout_save, STDOUT_FILENO);

  /* Close response file.  */
  close (redir_handle);

  if (pid == -1)
    {
      fatal (_("%s %s: %s"), errmsg_fmt, errmsg_arg, strerror (errno));
      return 1;
    }

  retcode = 0;
  pid = pwait (pid, &wait_status, 0);

  if (pid == -1)
    {
      fatal (_("wait: %s"), strerror (errno));
      retcode = 1;
    }
  else if (WIFSIGNALED (wait_status))
    {
      fatal (_("subprocess got fatal signal %d"), WTERMSIG (wait_status));
      retcode = 1;
    }
  else if (WIFEXITED (wait_status))
    {
      if (WEXITSTATUS (wait_status) != 0)
	{
	  fatal (_("%s exited with status %d"), cmd,
	         WEXITSTATUS (wait_status));
	  retcode = 1;
	}
    }
  else
    retcode = 1;

  return retcode;
}