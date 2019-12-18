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
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  task_region_footprint; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* current_task () ; 
 scalar_t__ vm_region_footprint ; 

boolean_t
task_self_region_footprint(void)
{
#if DEVELOPMENT || DEBUG
	if (vm_region_footprint) {
		/* system-wide override */
		return TRUE;
	}
#endif /* DEVELOPMENT || DEBUG */
	return current_task()->task_region_footprint;
}