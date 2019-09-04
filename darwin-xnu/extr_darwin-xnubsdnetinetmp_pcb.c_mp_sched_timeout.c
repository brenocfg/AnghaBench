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
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  lck_mtx_convert_spin (int /*<<< orphan*/ *) ; 
 scalar_t__ mp_garbage_collecting ; 
 scalar_t__ mp_ticking ; 
 int /*<<< orphan*/  mp_timeout ; 
 int /*<<< orphan*/  mp_timeout_lock ; 
 scalar_t__ mp_timeout_run ; 
 int /*<<< orphan*/  timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mp_sched_timeout(void)
{
	LCK_MTX_ASSERT(&mp_timeout_lock, LCK_MTX_ASSERT_OWNED);

	if (!mp_timeout_run && (mp_garbage_collecting || mp_ticking)) {
		lck_mtx_convert_spin(&mp_timeout_lock);
		mp_timeout_run = TRUE;
		timeout(mp_timeout, NULL, hz);
	}
}