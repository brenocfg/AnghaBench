#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ tid; struct TYPE_10__* next; struct TYPE_10__* thread_list; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ procinfo ;

/* Variables and functions */
 TYPE_1__* find_procinfo_or_die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,TYPE_1__*,void*) ; 

int
proc_iterate_over_threads (procinfo *pi,
			   int (*func) (procinfo *, procinfo *, void *),
			   void *ptr)
{
  procinfo *thread, *next;
  int retval = 0;

  /*
   * We should never have to apply this operation to any procinfo
   * except the one for the main process.  If that ever changes
   * for any reason, then take out the following clause and
   * replace it with one that makes sure the ctl_fd is open.
   */

  if (pi->tid != 0)
    pi = find_procinfo_or_die (pi->pid, 0);

  for (thread = pi->thread_list; thread != NULL; thread = next)
    {
      next = thread->next;	/* in case thread is destroyed */
      if ((retval = (*func) (pi, thread, ptr)) != 0)
	break;
    }

  return retval;
}