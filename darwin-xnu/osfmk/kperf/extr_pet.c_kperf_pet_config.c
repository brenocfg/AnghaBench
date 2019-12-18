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
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_INFO (int /*<<< orphan*/ ,int,unsigned int) ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  PERF_PET_THREAD ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 unsigned int pet_action_id ; 
 scalar_t__ pet_init () ; 
 int /*<<< orphan*/  pet_lock ; 
 int /*<<< orphan*/  pet_start () ; 
 int /*<<< orphan*/  pet_stop () ; 

void
kperf_pet_config(unsigned int action_id)
{
	kern_return_t kr = pet_init();
	if (kr != KERN_SUCCESS) {
		return;
	}

	lck_mtx_lock(pet_lock);

	BUF_INFO(PERF_PET_THREAD, 3, action_id);

	if (action_id == 0) {
		pet_stop();
	} else {
		pet_start();
	}

	pet_action_id = action_id;

	lck_mtx_unlock(pet_lock);
}