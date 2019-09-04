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

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_garbage_collecting ; 
 int /*<<< orphan*/  mp_sched_timeout () ; 
 int /*<<< orphan*/  mp_timeout_lock ; 

void
mp_gc_sched(void)
{
	lck_mtx_lock_spin(&mp_timeout_lock);
	mp_garbage_collecting = TRUE;
	mp_sched_timeout();
	lck_mtx_unlock(&mp_timeout_lock);
}