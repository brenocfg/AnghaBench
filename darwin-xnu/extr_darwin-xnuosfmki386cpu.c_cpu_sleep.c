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
struct TYPE_3__ {int /*<<< orphan*/  cpu_id; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  PE_cpu_machine_quiesce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_thread_halt () ; 
 TYPE_1__* current_cpu_datap () ; 

void
cpu_sleep(void)
{
	cpu_data_t	*cdp = current_cpu_datap();

	PE_cpu_machine_quiesce(cdp->cpu_id);

	cpu_thread_halt();
}