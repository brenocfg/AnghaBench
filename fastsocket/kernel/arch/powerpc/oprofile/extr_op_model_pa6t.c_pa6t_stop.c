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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  PA6T_MMCR0_FCM0 ; 
 int /*<<< orphan*/  SPRN_PA6T_MMCR0 ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ oprofile_running ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void pa6t_stop(void)
{
	u64 mmcr0;

	/* freeze counters */
	mmcr0 = mfspr(SPRN_PA6T_MMCR0);
	mmcr0 |= PA6T_MMCR0_FCM0;
	mtspr(SPRN_PA6T_MMCR0, mmcr0);

	oprofile_running = 0;

	pr_debug("stop on cpu %d, mmcr0 %llx\n", smp_processor_id(), mmcr0);
}