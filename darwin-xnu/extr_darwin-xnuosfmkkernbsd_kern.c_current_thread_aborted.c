#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int sched_flags; int options; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int THREAD_UNINT ; 
 int TH_OPT_INTMASK ; 
 int TH_SFLAG_ABORT ; 
 int TH_SFLAG_ABORTED_MASK ; 
 int TH_SFLAG_ABORTSAFELY ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 

boolean_t
current_thread_aborted (
		void)
{
	thread_t th = current_thread();
	spl_t s;

	if ((th->sched_flags & TH_SFLAG_ABORTED_MASK) == TH_SFLAG_ABORT &&
			(th->options & TH_OPT_INTMASK) != THREAD_UNINT)
		return (TRUE);
	if (th->sched_flags & TH_SFLAG_ABORTSAFELY) {
		s = splsched();
		thread_lock(th);
		if (th->sched_flags & TH_SFLAG_ABORTSAFELY)
			th->sched_flags &= ~TH_SFLAG_ABORTED_MASK;
		thread_unlock(th);
		splx(s);
	}
	return FALSE;
}