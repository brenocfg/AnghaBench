#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  spl_t ;
struct TYPE_7__ {int sched_flags; } ;

/* Variables and functions */
 int TH_SFLAG_ABORT ; 
 int TH_SFLAG_ABORTSAFELY ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_depress_abort_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_set_apc_ast_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 

__attribute__((used)) static void
act_abort(
	thread_t	thread)
{
	spl_t		s = splsched();

	thread_lock(thread);

	if (!(thread->sched_flags & TH_SFLAG_ABORT)) {
		thread->sched_flags |= TH_SFLAG_ABORT;
		thread_set_apc_ast_locked(thread);
		thread_depress_abort_locked(thread);
	} else {
		thread->sched_flags &= ~TH_SFLAG_ABORTSAFELY;
	}

	thread_unlock(thread);
	splx(s);
}