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
typedef  int /*<<< orphan*/  ptid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 int PTRACE_CONT ; 
 int PTRACE_CONT_ONE ; 
 int PTRACE_SINGLESTEP ; 
 int PTRACE_SINGLESTEP_ONE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  ptrace (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_signal_to_host (int) ; 

void
child_resume (ptid_t ptid, int step, enum target_signal signal)
{
  int func;
  int pid = PIDGET (ptid);

  errno = 0;

  /* If pid == -1, then we want to step/continue all threads, else
     we only want to step/continue a single thread.  */
  if (pid == -1)
    {
      pid = PIDGET (inferior_ptid);
      func = step ? PTRACE_SINGLESTEP : PTRACE_CONT;
    }
  else
    func = step ? PTRACE_SINGLESTEP_ONE : PTRACE_CONT_ONE;


  /* An address of (PTRACE_ARG3_TYPE)1 tells ptrace to continue from where
     it was.  (If GDB wanted it to start some other way, we have already
     written a new PC value to the child.)

     If this system does not support PT_STEP, a higher level function will
     have called single_step() to transmute the step request into a
     continue request (by setting breakpoints on all possible successor
     instructions), so we don't have to worry about that here.  */

  ptrace (func, pid, (PTRACE_ARG3_TYPE) 1, target_signal_to_host (signal));

  if (errno)
    perror_with_name ("ptrace");
}