#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
struct TYPE_5__ {size_t count; size_t maxcount; TYPE_1__* atts; TYPE_3__* map; } ;
typedef  TYPE_2__ krt_t ;
struct TYPE_6__ {uintptr_t thread; int valid; int /*<<< orphan*/  command; } ;
typedef  TYPE_3__ kd_threadmap ;
struct TYPE_4__ {int pid; int /*<<< orphan*/  task_comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ thread_tid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kdbg_resolve_map(thread_t th_act, void *opaque)
{
	kd_threadmap *mapptr;
	krt_t *t = (krt_t *)opaque;

	if (t->count < t->maxcount) {
		mapptr = &t->map[t->count];
		mapptr->thread  = (uintptr_t)thread_tid(th_act);

		(void) strlcpy (mapptr->command, t->atts->task_comm,
				sizeof(t->atts->task_comm));
		/*
		 * Some kernel threads have no associated pid.
		 * We still need to mark the entry as valid.
		 */
		if (t->atts->pid)
			mapptr->valid = t->atts->pid;
		else
			mapptr->valid = 1;

		t->count++;
	}
}