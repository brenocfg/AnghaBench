#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* cpu_running; void* cpu_boot_complete; int /*<<< orphan*/  cpu_id; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  PE_cpu_machine_init (int /*<<< orphan*/ ,int) ; 
 void* TRUE ; 
 TYPE_1__* current_cpu_datap () ; 
 int /*<<< orphan*/  ml_init_interrupt () ; 
 int /*<<< orphan*/  vmx_cpu_init () ; 

void
cpu_machine_init(
	void)
{
	cpu_data_t	*cdp = current_cpu_datap();

	PE_cpu_machine_init(cdp->cpu_id, !cdp->cpu_boot_complete);
	cdp->cpu_boot_complete = TRUE;
	cdp->cpu_running = TRUE;
	ml_init_interrupt();

#if CONFIG_VMX
	/* initialize VMX for every CPU */
	vmx_cpu_init();
#endif
}