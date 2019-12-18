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
struct tidinfo {int state; } ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 struct tidinfo* procfs_thread_info (int,int) ; 
 int ptid_get_pid (int /*<<< orphan*/ ) ; 
 int ptid_get_tid (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,int) ; 

char *
procfs_pid_to_str (ptid_t ptid)
{
  static char buf[1024];
  int pid, tid, n;
  struct tidinfo *tip;

  pid = ptid_get_pid (ptid);
  tid = ptid_get_tid (ptid);

  n = snprintf (buf, 1023, "process %d", pid);

#if 0				/* NYI */
  tip = procfs_thread_info (pid, tid);
  if (tip != NULL)
    snprintf (&buf[n], 1023, " (state = 0x%02x)", tip->state);
#endif

  return buf;
}