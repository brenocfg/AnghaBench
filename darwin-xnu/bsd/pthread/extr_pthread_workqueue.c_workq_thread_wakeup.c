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
struct uthread {int uu_workq_flags; int /*<<< orphan*/  uu_thread; } ;

/* Variables and functions */
 int UT_WORKQ_IDLE_CLEANUP ; 
 int /*<<< orphan*/  thread_wakeup_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_parked_wait_event (struct uthread*) ; 

__attribute__((used)) static inline void
workq_thread_wakeup(struct uthread *uth)
{
	if ((uth->uu_workq_flags & UT_WORKQ_IDLE_CLEANUP) == 0) {
		thread_wakeup_thread(workq_parked_wait_event(uth), uth->uu_thread);
	}
}