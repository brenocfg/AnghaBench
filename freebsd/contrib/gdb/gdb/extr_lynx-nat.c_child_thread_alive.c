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

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTRACE_THREADUSER ; 
 int ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
child_thread_alive (ptid_t ptid)
{
  int pid = PIDGET (ptid);

  /* Arggh.  Apparently pthread_kill only works for threads within
     the process that calls pthread_kill.

     We want to avoid the lynx signal extensions as they simply don't
     map well to the generic gdb interface we want to keep.

     All we want to do is determine if a particular thread is alive;
     it appears as if we can just make a harmless thread specific
     ptrace call to do that.  */
  return (ptrace (PTRACE_THREADUSER, pid, 0, 0) != -1);
}