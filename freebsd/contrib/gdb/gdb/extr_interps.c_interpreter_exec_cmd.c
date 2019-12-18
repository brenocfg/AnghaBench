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
struct interp {int dummy; } ;

/* Variables and functions */
 char** buildargv (char*) ; 
 struct interp* current_interpreter ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  interp_exec (struct interp*,char*) ; 
 struct interp* interp_lookup (char*) ; 
 int /*<<< orphan*/  interp_set (struct interp*) ; 
 int interp_set_quiet (struct interp*,int) ; 

__attribute__((used)) static void
interpreter_exec_cmd (char *args, int from_tty)
{
  struct interp *old_interp, *interp_to_use;
  char **prules = NULL;
  char **trule = NULL;
  unsigned int nrules;
  unsigned int i;
  int old_quiet, use_quiet;

  prules = buildargv (args);
  if (prules == NULL)
    {
      error ("unable to parse arguments");
    }

  nrules = 0;
  if (prules != NULL)
    {
      for (trule = prules; *trule != NULL; trule++)
	{
	  nrules++;
	}
    }

  if (nrules < 2)
    error ("usage: interpreter-exec <interpreter> [ <command> ... ]");

  old_interp = current_interpreter;

  interp_to_use = interp_lookup (prules[0]);
  if (interp_to_use == NULL)
    error ("Could not find interpreter \"%s\".", prules[0]);

  /* Temporarily set interpreters quiet */
  old_quiet = interp_set_quiet (old_interp, 1);
  use_quiet = interp_set_quiet (interp_to_use, 1);

  if (!interp_set (interp_to_use))
    error ("Could not switch to interpreter \"%s\".", prules[0]);

  for (i = 1; i < nrules; i++)
    {
      if (!interp_exec (interp_to_use, prules[i]))
	{
	  interp_set (old_interp);
	  interp_set_quiet (interp_to_use, old_quiet);
	  error ("error in command: \"%s\".", prules[i]);
	  break;
	}
    }

  interp_set (old_interp);
  interp_set_quiet (interp_to_use, use_quiet);
  interp_set_quiet (old_interp, old_quiet);
}