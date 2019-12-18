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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 char* child_pid_to_str (int /*<<< orphan*/ ) ; 
 char* hppa_tid_to_str (int /*<<< orphan*/ ) ; 
 scalar_t__ is_process_id (int /*<<< orphan*/ ) ; 
 int pid_to_thread_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

char *
hppa_pid_or_tid_to_str (ptid_t ptid)
{
  static char buf[100];		/* Static because address returned. */
  pid_t id = PIDGET (ptid);

  /* Does this appear to be a process?  If so, print it that way. */
  if (is_process_id (id))
    return child_pid_to_str (ptid);

  /* Else, print both the GDB thread number and the system thread id. */
  sprintf (buf, "thread %d (", pid_to_thread_id (ptid));
  strcat (buf, hppa_tid_to_str (ptid));
  strcat (buf, ")\0");

  return buf;
}