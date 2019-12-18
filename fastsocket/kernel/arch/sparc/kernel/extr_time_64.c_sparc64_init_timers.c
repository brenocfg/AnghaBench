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
struct device_node {int dummy; } ;
struct TYPE_2__ {unsigned long clock_tick; } ;

/* Variables and functions */
 int /*<<< orphan*/  hbtick_operations ; 
 TYPE_1__ local_cpu_data () ; 
 struct device_node* of_find_node_by_path (char*) ; 
 unsigned long of_getintprop_default (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ spitfire ; 
 int /*<<< orphan*/  stick_operations ; 
 int /*<<< orphan*/  tick_operations ; 
 int /*<<< orphan*/ * tick_ops ; 
 scalar_t__ tlb_type ; 

__attribute__((used)) static unsigned long sparc64_init_timers(void)
{
	struct device_node *dp;
	unsigned long freq;

	dp = of_find_node_by_path("/");
	if (tlb_type == spitfire) {
		unsigned long ver, manuf, impl;

		__asm__ __volatile__ ("rdpr %%ver, %0"
				      : "=&r" (ver));
		manuf = ((ver >> 48) & 0xffff);
		impl = ((ver >> 32) & 0xffff);
		if (manuf == 0x17 && impl == 0x13) {
			/* Hummingbird, aka Ultra-IIe */
			tick_ops = &hbtick_operations;
			freq = of_getintprop_default(dp, "stick-frequency", 0);
		} else {
			tick_ops = &tick_operations;
			freq = local_cpu_data().clock_tick;
		}
	} else {
		tick_ops = &stick_operations;
		freq = of_getintprop_default(dp, "stick-frequency", 0);
	}

	return freq;
}