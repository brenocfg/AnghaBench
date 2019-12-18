#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct op_counter_config {scalar_t__ enabled; } ;
struct TYPE_2__ {int num_pmcs; } ;

/* Variables and functions */
 int PA6T_MMCR0_HANDDIS ; 
 int /*<<< orphan*/  SPRN_PA6T_MMCR0 ; 
 int /*<<< orphan*/  ctr_write (int,unsigned long) ; 
 TYPE_1__* cur_cpu_spec ; 
 int mmcr0_val ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int oprofile_running ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 unsigned long* reset_value ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static int pa6t_start(struct op_counter_config *ctr)
{
	int i;

	/* Hold off event counting until rfid */
	u64 mmcr0 = mmcr0_val | PA6T_MMCR0_HANDDIS;

	for (i = 0; i < cur_cpu_spec->num_pmcs; i++)
		if (ctr[i].enabled)
			ctr_write(i, reset_value[i]);
		else
			ctr_write(i, 0UL);

	mtspr(SPRN_PA6T_MMCR0, mmcr0);

	oprofile_running = 1;

	pr_debug("start on cpu %d, mmcr0 %llx\n", smp_processor_id(), mmcr0);

	return 0;
}