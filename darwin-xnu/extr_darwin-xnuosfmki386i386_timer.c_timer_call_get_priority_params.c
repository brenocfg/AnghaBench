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
typedef  int /*<<< orphan*/  timer_coalescing_priority_params_ns_t ;

/* Variables and functions */
 int /*<<< orphan*/  tcoal_prio_params_init ; 

timer_coalescing_priority_params_ns_t * timer_call_get_priority_params(void)
{
	return &tcoal_prio_params_init;
}