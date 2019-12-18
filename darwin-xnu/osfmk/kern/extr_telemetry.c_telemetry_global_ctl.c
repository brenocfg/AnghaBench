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

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  telemetry_sample_all_tasks ; 

void
telemetry_global_ctl(int enable_disable)
{
	if (enable_disable == 1) {
		telemetry_sample_all_tasks = TRUE;
	} else {
		telemetry_sample_all_tasks = FALSE;
	}
}