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
struct adb_request {int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int PMU_INT_ADB ; 
 int PMU_INT_TICK ; 
 scalar_t__ PMU_KEYLARGO_BASED ; 
 int /*<<< orphan*/  PMU_RESET ; 
 int /*<<< orphan*/  PMU_SET_INTR_MASK ; 
 int drop_interrupts ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 scalar_t__ pmu_kind ; 
 int /*<<< orphan*/  pmu_poll () ; 
 int /*<<< orphan*/  pmu_request (struct adb_request*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pmu_wait_complete (struct adb_request*) ; 
 int /*<<< orphan*/ * via ; 

void
pmu_restart(void)
{
	struct adb_request req;

	if (via == NULL)
		return;

	local_irq_disable();

	drop_interrupts = 1;
	
	if (pmu_kind != PMU_KEYLARGO_BASED) {
		pmu_request(&req, NULL, 2, PMU_SET_INTR_MASK, PMU_INT_ADB |
						PMU_INT_TICK );
		while(!req.complete)
			pmu_poll();
	}

	pmu_request(&req, NULL, 1, PMU_RESET);
	pmu_wait_complete(&req);
	for (;;)
		;
}