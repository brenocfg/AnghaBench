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
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  kalloc (int) ; 
 int /*<<< orphan*/  lck_mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pet_lock ; 
 scalar_t__ pet_running ; 
 int /*<<< orphan*/  pet_sample ; 

void
pet_start(void)
{
	lck_mtx_assert(pet_lock, LCK_MTX_ASSERT_OWNED);

	if (pet_running) {
		return;
	}

	pet_sample = kalloc(sizeof(struct kperf_sample));
	if (!pet_sample) {
		return;
	}

	pet_running = TRUE;
}