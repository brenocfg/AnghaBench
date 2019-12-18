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
struct TYPE_2__ {int /*<<< orphan*/  active_mm; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ TLBSTATE_OK ; 
 TYPE_1__ cpu_tlbstate ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_cr3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_cpumask (scalar_t__) ; 
 scalar_t__ percpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swapper_pg_dir ; 

void leave_mm(int cpu)
{
	if (percpu_read(cpu_tlbstate.state) == TLBSTATE_OK)
		BUG();
	cpumask_clear_cpu(cpu,
			  mm_cpumask(percpu_read(cpu_tlbstate.active_mm)));
	load_cr3(swapper_pg_dir);
}