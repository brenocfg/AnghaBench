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
 int PIDGET (int /*<<< orphan*/ ) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  child_ops ; 
 int /*<<< orphan*/  detach (int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 char* get_exec_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
child_detach (char *args, int from_tty)
{
#ifdef ATTACH_DETACH
  {
    int siggnal = 0;
    int pid = PIDGET (inferior_ptid);

    if (from_tty)
      {
	char *exec_file = get_exec_file (0);
	if (exec_file == 0)
	  exec_file = "";
	printf_unfiltered ("Detaching from program: %s, %s\n", exec_file,
			   target_pid_to_str (pid_to_ptid (pid)));
	gdb_flush (gdb_stdout);
      }
    if (args)
      siggnal = atoi (args);

    detach (siggnal);

    inferior_ptid = null_ptid;
    unpush_target (&child_ops);
  }
#else
  error ("This version of Unix does not support detaching a process.");
#endif
}