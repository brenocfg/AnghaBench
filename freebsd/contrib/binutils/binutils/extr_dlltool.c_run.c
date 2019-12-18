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
 int PEXECUTE_ONE ; 
 int PEXECUTE_SEARCH ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 char* WTERMSIG (int) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 char** alloca (int) ; 
 char* choose_temp_base () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,char*) ; 
 int /*<<< orphan*/  inform (char*,...) ; 
 int /*<<< orphan*/  non_fatal (char*,char const*,scalar_t__) ; 
 int pexecute (char const*,char* const*,int /*<<< orphan*/ ,char*,char**,char**,int) ; 
 int /*<<< orphan*/  program_name ; 
 int pwait (int,int*,int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
run (const char *what, char *args)
{
  char *s;
  int pid, wait_status;
  int i;
  const char **argv;
  char *errmsg_fmt, *errmsg_arg;
  char *temp_base = choose_temp_base ();

  inform ("run: %s %s", what, args);

  /* Count the args */
  i = 0;
  for (s = args; *s; s++)
    if (*s == ' ')
      i++;
  i++;
  argv = alloca (sizeof (char *) * (i + 3));
  i = 0;
  argv[i++] = what;
  s = args;
  while (1)
    {
      while (*s == ' ')
	++s;
      argv[i++] = s;
      while (*s != ' ' && *s != 0)
	s++;
      if (*s == 0)
	break;
      *s++ = 0;
    }
  argv[i++] = NULL;

  pid = pexecute (argv[0], (char * const *) argv, program_name, temp_base,
		  &errmsg_fmt, &errmsg_arg, PEXECUTE_ONE | PEXECUTE_SEARCH);

  if (pid == -1)
    {
      inform (strerror (errno));

      fatal (errmsg_fmt, errmsg_arg);
    }

  pid = pwait (pid, & wait_status, 0);

  if (pid == -1)
    {
      /* xgettext:c-format */
      fatal (_("wait: %s"), strerror (errno));
    }
  else if (WIFSIGNALED (wait_status))
    {
      /* xgettext:c-format */
      fatal (_("subprocess got fatal signal %d"), WTERMSIG (wait_status));
    }
  else if (WIFEXITED (wait_status))
    {
      if (WEXITSTATUS (wait_status) != 0)
	/* xgettext:c-format */
	non_fatal (_("%s exited with status %d"),
		   what, WEXITSTATUS (wait_status));
    }
  else
    abort ();
}