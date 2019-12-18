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
typedef  int u64 ;
struct op_counter_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_PA6T_MMCR0 ; 
 int /*<<< orphan*/  SPRN_PA6T_MMCR1 ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 int mmcr0_val ; 
 int mmcr1_val ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static int pa6t_cpu_setup(struct op_counter_config *ctr)
{
	u64 mmcr0 = mmcr0_val;
	u64 mmcr1 = mmcr1_val;

	/* Default is all PMCs off */
	mmcr0 &= ~(0x3FUL);
	mtspr(SPRN_PA6T_MMCR0, mmcr0);

	/* program selected programmable events in */
	mtspr(SPRN_PA6T_MMCR1, mmcr1);

	pr_debug("setup on cpu %d, mmcr0 %016lx\n", smp_processor_id(),
		mfspr(SPRN_PA6T_MMCR0));
	pr_debug("setup on cpu %d, mmcr1 %016lx\n", smp_processor_id(),
		mfspr(SPRN_PA6T_MMCR1));

	return 0;
}