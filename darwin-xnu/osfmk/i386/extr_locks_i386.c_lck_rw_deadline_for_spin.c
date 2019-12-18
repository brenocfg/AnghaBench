#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ lck_rw_shared_count; scalar_t__ lck_w_waiting; scalar_t__ lck_r_waiting; scalar_t__ lck_rw_can_sleep; } ;
typedef  TYPE_1__ lck_rw_t ;
struct TYPE_5__ {scalar_t__ max_cpus; } ;

/* Variables and functions */
 scalar_t__ MutexSpin ; 
 scalar_t__ mach_absolute_time () ; 
 TYPE_2__ machine_info ; 

__attribute__((used)) static inline uint64_t
lck_rw_deadline_for_spin(lck_rw_t *lck)
{
	if (lck->lck_rw_can_sleep) {
		if (lck->lck_r_waiting || lck->lck_w_waiting || lck->lck_rw_shared_count > machine_info.max_cpus) {
			/*
			 * there are already threads waiting on this lock... this
			 * implies that they have spun beyond their deadlines waiting for 
			 * the desired state to show up so we will not bother spinning at this time...
			 *   or
			 * the current number of threads sharing this lock exceeds our capacity to run them
			 * concurrently and since all states we're going to spin for require the rw_shared_count
			 * to be at 0, we'll not bother spinning since the latency for this to happen is
			 * unpredictable...
			 */
			return (mach_absolute_time());
		}
		return (mach_absolute_time() + MutexSpin);
	} else
		return (mach_absolute_time() + (100000LL * 1000000000LL));
}