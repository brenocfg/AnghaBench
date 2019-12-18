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
 int PEXECUTE_FIRST ; 
 int PEXECUTE_LAST ; 
 int PEXECUTE_SEARCH ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 size_t aux_info_file_name_index ; 
 int /*<<< orphan*/  aux_info_suffix ; 
 int /*<<< orphan*/ * compile_params ; 
 int /*<<< orphan*/  concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 size_t input_file_name_index ; 
 int /*<<< orphan*/  munge_compile_params (char*) ; 
 int /*<<< orphan*/  notice (char*,char*,char*,...) ; 
 int pexecute (int /*<<< orphan*/ ,char* const*,char*,int /*<<< orphan*/ *,char**,char**,int) ; 
 char* pname ; 
 int pwait (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quiet_flag ; 
 int /*<<< orphan*/  shortpath (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 char* xstrerror (int) ; 

__attribute__((used)) static int
gen_aux_info_file (const char *base_filename)
{
  if (!input_file_name_index)
    munge_compile_params ("");

  /* Store the full source file name in the argument vector.  */
  compile_params[input_file_name_index] = shortpath (NULL, base_filename);
  /* Add .X to source file name to get aux-info file name.  */
  compile_params[aux_info_file_name_index] =
    concat (compile_params[input_file_name_index], aux_info_suffix, NULL);

  if (!quiet_flag)
    notice ("%s: compiling '%s'\n",
	    pname, compile_params[input_file_name_index]);

  {
    char *errmsg_fmt, *errmsg_arg;
    int wait_status, pid;

    pid = pexecute (compile_params[0], (char * const *) compile_params,
		    pname, NULL, &errmsg_fmt, &errmsg_arg,
		    PEXECUTE_FIRST | PEXECUTE_LAST | PEXECUTE_SEARCH);

    if (pid == -1)
      {
	int errno_val = errno;
	fprintf (stderr, "%s: ", pname);
	fprintf (stderr, errmsg_fmt, errmsg_arg);
	fprintf (stderr, ": %s\n", xstrerror (errno_val));
	return 0;
      }

    pid = pwait (pid, &wait_status, 0);
    if (pid == -1)
      {
	notice ("%s: wait: %s\n", pname, xstrerror (errno));
	return 0;
      }
    if (WIFSIGNALED (wait_status))
      {
	notice ("%s: subprocess got fatal signal %d\n",
		pname, WTERMSIG (wait_status));
	return 0;
      }
    if (WIFEXITED (wait_status))
      {
	if (WEXITSTATUS (wait_status) != 0)
	  {
	    notice ("%s: %s exited with status %d\n",
		    pname, compile_params[0], WEXITSTATUS (wait_status));
	    return 0;
	  }
	return 1;
      }
    gcc_unreachable ();
  }
}