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
typedef  int /*<<< orphan*/  procinfo ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 int TIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_procinfo (int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

char *
procfs_pid_to_str (ptid_t ptid)
{
  static char buf[80];
  int proc, thread;
  procinfo *pi;

  proc    = PIDGET (ptid);
  thread  = TIDGET (ptid);
  pi      = find_procinfo (proc, thread);

  if (thread == 0)
    sprintf (buf, "Process %d", proc);
  else
    sprintf (buf, "LWP %d", thread);
  return &buf[0];
}