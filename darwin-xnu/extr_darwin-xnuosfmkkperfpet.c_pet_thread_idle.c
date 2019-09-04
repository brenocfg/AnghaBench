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
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  LCK_SLEEP_DEFAULT ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  lck_mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pet_action_id ; 
 int /*<<< orphan*/  pet_lock ; 

__attribute__((used)) static void
pet_thread_idle(void)
{
	lck_mtx_assert(pet_lock, LCK_MTX_ASSERT_OWNED);

	(void)lck_mtx_sleep(pet_lock, LCK_SLEEP_DEFAULT, &pet_action_id,
	                    THREAD_UNINT);
}