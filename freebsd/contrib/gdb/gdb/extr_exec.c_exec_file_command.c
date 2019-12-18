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
 char** buildargv (char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  exec_file_attach (char*,int) ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  make_cleanup_freeargv (char**) ; 
 int /*<<< orphan*/  nomem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_preopen (int) ; 
 char* tilde_expand (char*) ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static void
exec_file_command (char *args, int from_tty)
{
  char **argv;
  char *filename;
  
  target_preopen (from_tty);

  if (args)
    {
      /* Scan through the args and pick up the first non option arg
         as the filename.  */

      argv = buildargv (args);
      if (argv == NULL)
        nomem (0);

      make_cleanup_freeargv (argv);

      for (; (*argv != NULL) && (**argv == '-'); argv++)
        {;
        }
      if (*argv == NULL)
        error ("No executable file name was specified");

      filename = tilde_expand (*argv);
      make_cleanup (xfree, filename);
      exec_file_attach (filename, from_tty);
    }
  else
    exec_file_attach (NULL, from_tty);
}