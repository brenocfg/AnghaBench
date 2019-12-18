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
 int /*<<< orphan*/  do_detach (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* get_exec_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  printf_filtered (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procfs_ops ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
procfs_detach (char *args, int from_tty)
{
  char *exec_file;
  int   signo = 0;

  if (from_tty)
    {
      exec_file = get_exec_file (0);
      if (exec_file == 0)
	exec_file = "";
      printf_filtered ("Detaching from program: %s %s\n",
	      exec_file, target_pid_to_str (inferior_ptid));
      fflush (stdout);
    }
  if (args)
    signo = atoi (args);

  do_detach (signo);
  inferior_ptid = null_ptid;
  unpush_target (&procfs_ops);		/* Pop out of handling an inferior */
}