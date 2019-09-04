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
struct TYPE_7__ {int state; scalar_t__ wake_active; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int TH_RUN ; 
 int TH_SUSP ; 
 int TH_WAIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_wakeup (scalar_t__*) ; 
 int /*<<< orphan*/  wake_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_unlock (TYPE_1__*) ; 

void
thread_unstop(
	thread_t	thread)
{
	spl_t		s = splsched();

	wake_lock(thread);
	thread_lock(thread);

	assert((thread->state & (TH_RUN|TH_WAIT|TH_SUSP)) != TH_SUSP);

	if (thread->state & TH_SUSP) {
		thread->state &= ~TH_SUSP;

		if (thread->wake_active) {
			thread->wake_active = FALSE;
			thread_unlock(thread);

			thread_wakeup(&thread->wake_active);
			wake_unlock(thread);
			splx(s);

			return;
		}
	}

	thread_unlock(thread);
	wake_unlock(thread);
	splx(s);
}