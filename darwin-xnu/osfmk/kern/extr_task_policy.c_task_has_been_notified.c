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
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {scalar_t__ low_mem_notified_critical; scalar_t__ low_mem_notified_warn; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int kVMPressureCritical ; 
 int kVMPressureWarning ; 

boolean_t
task_has_been_notified(task_t task, int pressurelevel)
{
	if (task == NULL) {
		return FALSE;
	}
	
	if (pressurelevel == kVMPressureWarning) 
		return (task->low_mem_notified_warn ? TRUE : FALSE);
	else if (pressurelevel == kVMPressureCritical) 
		return (task->low_mem_notified_critical ? TRUE : FALSE);
	else 
		return TRUE;
}