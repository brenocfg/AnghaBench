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
 int /*<<< orphan*/  destroy_procinfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_procinfo (int,int) ; 
 int /*<<< orphan*/  proc_get_status (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
procfs_thread_alive (ptid_t ptid)
{
  int proc, thread;
  procinfo *pi;

  proc    = PIDGET (ptid);
  thread  = TIDGET (ptid);
  /* If I don't know it, it ain't alive! */
  if ((pi = find_procinfo (proc, thread)) == NULL)
    return 0;

  /* If I can't get its status, it ain't alive!
     What's more, I need to forget about it!  */
  if (!proc_get_status (pi))
    {
      destroy_procinfo (pi);
      return 0;
    }
  /* I couldn't have got its status if it weren't alive, so it's alive.  */
  return 1;
}