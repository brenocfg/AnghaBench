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
struct kperf_sample {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lck_mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pet_initted ; 
 int /*<<< orphan*/  pet_lock ; 
 int /*<<< orphan*/  pet_running ; 
 int /*<<< orphan*/ * pet_sample ; 
 int /*<<< orphan*/ * pet_tasks ; 
 scalar_t__ pet_tasks_count ; 
 scalar_t__ pet_tasks_size ; 
 int /*<<< orphan*/ * pet_threads ; 
 scalar_t__ pet_threads_count ; 
 scalar_t__ pet_threads_size ; 

void
pet_stop(void)
{
	lck_mtx_assert(pet_lock, LCK_MTX_ASSERT_OWNED);

	if (!pet_initted) {
		return;
	}

	if (pet_tasks != NULL) {
		assert(pet_tasks_size != 0);
		kfree(pet_tasks, pet_tasks_size);

		pet_tasks = NULL;
		pet_tasks_size = 0;
		pet_tasks_count = 0;
	}

	if (pet_threads != NULL) {
		assert(pet_threads_size != 0);
		kfree(pet_threads, pet_threads_size);

		pet_threads = NULL;
		pet_threads_size = 0;
		pet_threads_count = 0;
	}

	if (pet_sample != NULL) {
		kfree(pet_sample, sizeof(struct kperf_sample));
		pet_sample = NULL;
	}

	pet_running = FALSE;
}