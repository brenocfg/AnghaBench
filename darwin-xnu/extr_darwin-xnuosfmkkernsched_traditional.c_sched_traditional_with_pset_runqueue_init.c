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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sched_timeshare_init () ; 
 int /*<<< orphan*/  sched_traditional_use_pset_runqueue ; 

__attribute__((used)) static void
sched_traditional_with_pset_runqueue_init(void)
{
	sched_timeshare_init();
	sched_traditional_use_pset_runqueue = TRUE;
}