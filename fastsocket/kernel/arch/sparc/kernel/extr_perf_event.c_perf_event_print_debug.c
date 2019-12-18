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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  (* read ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_1__* pcr_ops ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  read_pic (int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  sparc_pmu ; 
 int /*<<< orphan*/  stub1 () ; 

void perf_event_print_debug(void)
{
	unsigned long flags;
	u64 pcr, pic;
	int cpu;

	if (!sparc_pmu)
		return;

	local_irq_save(flags);

	cpu = smp_processor_id();

	pcr = pcr_ops->read();
	read_pic(pic);

	pr_info("\n");
	pr_info("CPU#%d: PCR[%016llx] PIC[%016llx]\n",
		cpu, pcr, pic);

	local_irq_restore(flags);
}