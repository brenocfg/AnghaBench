#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * thread_call_t ;
typedef  TYPE_2__* proc_t ;
struct TYPE_6__ {int /*<<< orphan*/  it_interval; } ;
struct TYPE_7__ {scalar_t__ p_refcount; scalar_t__ p_ractive; int /*<<< orphan*/ * p_rcall; TYPE_1__ p_realtimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/  proc_spinlock (TYPE_2__*) ; 
 int /*<<< orphan*/  proc_spinunlock (TYPE_2__*) ; 
 scalar_t__ thread_call_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_call_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timerclear (int /*<<< orphan*/ *) ; 

void
proc_free_realitimer(proc_t p)
{
	proc_spinlock(p);

	assert(p->p_rcall != NULL);
	assert(p->p_refcount == 0);

	timerclear(&p->p_realtimer.it_interval);

	if (thread_call_cancel(p->p_rcall)) {
		assert(p->p_ractive > 0);
		p->p_ractive--;
	}

	while (p->p_ractive > 0) {
		proc_spinunlock(p);

		delay(1);

		proc_spinlock(p);
	}

	thread_call_t call = p->p_rcall;
	p->p_rcall = NULL;

	proc_spinunlock(p);

	thread_call_free(call);
}