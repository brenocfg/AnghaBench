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
typedef  TYPE_1__* task_t ;
struct TYPE_3__ {scalar_t__ low_mem_notified_critical; scalar_t__ low_mem_notified_warn; } ;

/* Variables and functions */
 int kVMPressureCritical ; 
 int kVMPressureWarning ; 

void
task_clear_has_been_notified(task_t task, int pressurelevel)
{
	if (task == NULL) {
		return;
	}
	
	if (pressurelevel == kVMPressureWarning)
		task->low_mem_notified_warn = 0;
	else if (pressurelevel == kVMPressureCritical)
		task->low_mem_notified_critical = 0;
}