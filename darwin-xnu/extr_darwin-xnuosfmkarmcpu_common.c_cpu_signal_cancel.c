#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cpu_signal; int /*<<< orphan*/  cpu_id; } ;
typedef  TYPE_1__ cpu_data_t ;
struct TYPE_5__ {int /*<<< orphan*/  cpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  PE_cpu_signal_cancel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SIGPdisabled ; 
 TYPE_2__* getCpuDatap () ; 

void
cpu_signal_cancel(cpu_data_t *target_proc)
{
	/* TODO: Should we care about the state of a core as far as squashing deferred IPIs goes? */
	if (!(target_proc->cpu_signal & SIGPdisabled)) {
		PE_cpu_signal_cancel(getCpuDatap()->cpu_id, target_proc->cpu_id);
	}
}