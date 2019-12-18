#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lwp_info {int cloned; int stopped; int resumed; int /*<<< orphan*/  status; } ;
typedef  int pid_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* to_attach ) (char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_LWP (int,int) ; 
 scalar_t__ ECHILD ; 
 int GET_PID (int /*<<< orphan*/ ) ; 
 scalar_t__ SIGSTOP ; 
 scalar_t__ WIFSTOPPED (int) ; 
 scalar_t__ WSTOPSIG (int) ; 
 int /*<<< orphan*/  W_STOPCODE (scalar_t__) ; 
 int /*<<< orphan*/  __WCLONE ; 
 struct lwp_info* add_lwp (int /*<<< orphan*/ ) ; 
 TYPE_1__ child_ops ; 
 scalar_t__ debug_lin_lwp ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  stub1 (char*,int) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lin_lwp_attach (char *args, int from_tty)
{
  struct lwp_info *lp;
  pid_t pid;
  int status;

  /* FIXME: We should probably accept a list of process id's, and
     attach all of them.  */
  child_ops.to_attach (args, from_tty);

  /* Add the initial process as the first LWP to the list.  */
  lp = add_lwp (BUILD_LWP (GET_PID (inferior_ptid), GET_PID (inferior_ptid)));

  /* Make sure the initial process is stopped.  The user-level threads
     layer might want to poke around in the inferior, and that won't
     work if things haven't stabilized yet.  */
  pid = waitpid (GET_PID (inferior_ptid), &status, 0);
  if (pid == -1 && errno == ECHILD)
    {
      warning ("%s is a cloned process", target_pid_to_str (inferior_ptid));

      /* Try again with __WCLONE to check cloned processes.  */
      pid = waitpid (GET_PID (inferior_ptid), &status, __WCLONE);
      lp->cloned = 1;
    }

  gdb_assert (pid == GET_PID (inferior_ptid)
	      && WIFSTOPPED (status) && WSTOPSIG (status) == SIGSTOP);

  lp->stopped = 1;

  /* Fake the SIGSTOP that core GDB expects.  */
  lp->status = W_STOPCODE (SIGSTOP);
  lp->resumed = 1;
  if (debug_lin_lwp)
    {
      fprintf_unfiltered (gdb_stdlog,
			  "LLA: waitpid %ld, faking SIGSTOP\n", (long) pid);
    }
}