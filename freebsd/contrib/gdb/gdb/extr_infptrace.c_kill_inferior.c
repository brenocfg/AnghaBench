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
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_KILL ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptrace_wait (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  target_mourn_inferior () ; 

void
kill_inferior (void)
{
  int status;
  int pid =  PIDGET (inferior_ptid);

  if (pid == 0)
    return;

  /* This once used to call "kill" to kill the inferior just in case
     the inferior was still running.  As others have noted in the past
     (kingdon) there shouldn't be any way to get here if the inferior
     is still running -- else there's a major problem elsewere in gdb
     and it needs to be fixed.

     The kill call causes problems under hpux10, so it's been removed;
     if this causes problems we'll deal with them as they arise.  */
  ptrace (PT_KILL, pid, (PTRACE_ARG3_TYPE) 0, 0);
  ptrace_wait (null_ptid, &status);
  target_mourn_inferior ();
}