#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pid; struct TYPE_4__* next; int /*<<< orphan*/  am_pseudo; } ;
typedef  TYPE_1__ thread_info ;
typedef  scalar_t__ pid_t ;
typedef  scalar_t__ lwpid_t ;
struct TYPE_5__ {TYPE_1__* head; } ;

/* Variables and functions */
 TYPE_1__* find_thread_info (scalar_t__) ; 
 scalar_t__ map_from_gdb_tid (int) ; 
 TYPE_2__ thread_head ; 

__attribute__((used)) static int
is_process_id (int pid)
{
  lwpid_t tid;
  thread_info *tinfo;
  pid_t this_pid;
  int this_pid_count;

  /* What does PID really represent?
   */
  tid = map_from_gdb_tid (pid);
  if (tid <= 0)
    return 0;			/* Actually, is probably an error... */

  tinfo = find_thread_info (tid);

  /* Does it appear to be a true thread?
   */
  if (!tinfo->am_pseudo)
    return 0;

  /* Else, it looks like it may be a process.  See if there's any other
   * threads with the same process ID, though.  If there are, then TID
   * just happens to be the first thread of several for this process.
   */
  this_pid = tinfo->pid;
  this_pid_count = 0;
  for (tinfo = thread_head.head; tinfo; tinfo = tinfo->next)
    {
      if (tinfo->pid == this_pid)
	this_pid_count++;
    }

  return (this_pid_count == 1);
}