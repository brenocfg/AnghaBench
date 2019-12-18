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
struct TYPE_4__ {int sched_flags; int /*<<< orphan*/  rwlock_count; } ;

/* Variables and functions */
 int TH_SFLAG_RW_PROMOTED ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  lck_rw_clear_promotion (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
clear_thread_rwlock_boost(void)
{
	thread_t thread = current_thread();

	if ((thread->rwlock_count-- == 1) && (thread->sched_flags & TH_SFLAG_RW_PROMOTED)) {

		lck_rw_clear_promotion(thread, 0);
	}
}