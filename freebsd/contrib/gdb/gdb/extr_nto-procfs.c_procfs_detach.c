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
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SignalKill (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int atoi (char*) ; 
 scalar_t__ attach_flag ; 
 int /*<<< orphan*/  close (int) ; 
 int ctl_fd ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 char* get_exec_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  init_thread_list () ; 
 int /*<<< orphan*/  nto_node () ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procfs_ops ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
procfs_detach (char *args, int from_tty)
{
  int siggnal = 0;

  if (from_tty)
    {
      char *exec_file = get_exec_file (0);
      if (exec_file == 0)
	exec_file = "";
      printf_unfiltered ("Detaching from program: %s %s\n",
			 exec_file, target_pid_to_str (inferior_ptid));
      gdb_flush (gdb_stdout);
    }
  if (args)
    siggnal = atoi (args);

  if (siggnal)
    SignalKill (nto_node(), PIDGET (inferior_ptid), 0, siggnal, 0, 0);

  close (ctl_fd);
  ctl_fd = -1;
  init_thread_list ();
  inferior_ptid = null_ptid;
  attach_flag = 0;
  unpush_target (&procfs_ops);	/* Pop out of handling an inferior.  */
}