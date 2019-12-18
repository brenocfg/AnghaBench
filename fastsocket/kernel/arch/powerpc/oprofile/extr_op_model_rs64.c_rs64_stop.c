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
 unsigned int MMCR0_FC ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mb () ; 
 unsigned int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void rs64_stop(void)
{
	unsigned int mmcr0;

	/* freeze counters */
	mmcr0 = mfspr(SPRN_MMCR0);
	mmcr0 |= MMCR0_FC;
	mtspr(SPRN_MMCR0, mmcr0);

	dbg("stop on cpu %d, mmcr0 %x\n", smp_processor_id(), mmcr0);

	mb();
}