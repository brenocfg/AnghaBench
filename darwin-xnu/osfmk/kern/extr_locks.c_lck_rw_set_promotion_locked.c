#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct TYPE_4__ {scalar_t__ rwlock_count; int sched_flags; } ;

/* Variables and functions */
 int LcksOpts ; 
 int TH_SFLAG_RW_PROMOTED ; 
 int /*<<< orphan*/  assert (int) ; 
 int disLkRWPrio ; 
 int /*<<< orphan*/  sched_thread_promote_reason (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

void
lck_rw_set_promotion_locked(thread_t thread)
{
	if (LcksOpts & disLkRWPrio)
		return;

	assert(thread->rwlock_count > 0);

	if (!(thread->sched_flags & TH_SFLAG_RW_PROMOTED))
		sched_thread_promote_reason(thread, TH_SFLAG_RW_PROMOTED, 0);
}