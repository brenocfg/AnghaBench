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
 int /*<<< orphan*/  BUF_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PERF_PET_SAMPLE ; 
 int /*<<< orphan*/  kperf_pet_gen ; 
 scalar_t__ lightweight_pet ; 
 int /*<<< orphan*/  pet_initted ; 
 int /*<<< orphan*/  pet_running ; 

void
kperf_pet_fire_before(void)
{
	if (!pet_initted || !pet_running) {
		return;
	}

	if (lightweight_pet) {
		BUF_INFO(PERF_PET_SAMPLE);
		OSIncrementAtomic(&kperf_pet_gen);
	}
}