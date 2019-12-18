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
 int EBUSY ; 
 scalar_t__ KPERF_SAMPLING_ON ; 
 int /*<<< orphan*/  kperf_lightweight_pet_active_update () ; 
 scalar_t__ kperf_sampling_status () ; 
 int lightweight_pet ; 

int
kperf_set_lightweight_pet(int val)
{
	if (kperf_sampling_status() == KPERF_SAMPLING_ON) {
		return EBUSY;
	}

	lightweight_pet = (val == 1);
	kperf_lightweight_pet_active_update();

	return 0;
}