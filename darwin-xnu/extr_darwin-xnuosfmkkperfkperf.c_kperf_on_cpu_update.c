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
 scalar_t__ kperf_kdebug_cswitch ; 
 scalar_t__ kperf_lazy_wait_action ; 
 scalar_t__ kperf_lightweight_pet_active ; 
 int kperf_on_cpu_active ; 

void
kperf_on_cpu_update(void)
{
	kperf_on_cpu_active = kperf_kdebug_cswitch ||
	                      kperf_lightweight_pet_active ||
	                      kperf_lazy_wait_action != 0;
}