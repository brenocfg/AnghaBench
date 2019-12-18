#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  thread_list; scalar_t__ status_valid; } ;
typedef  TYPE_1__ procinfo ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_one_procinfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  proc_get_status (TYPE_1__*) ; 

int
proc_delete_dead_threads (procinfo *parent, procinfo *thread, void *ignore)
{
  if (thread && parent)	/* sanity */
    {
      thread->status_valid = 0;
      if (!proc_get_status (thread))
	destroy_one_procinfo (&parent->thread_list, thread);
    }
  return 0;	/* keep iterating */
}