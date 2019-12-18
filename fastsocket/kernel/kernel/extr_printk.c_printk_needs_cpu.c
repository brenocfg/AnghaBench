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
 int /*<<< orphan*/  cpu_is_offline (int) ; 
 int per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk_pending ; 
 int /*<<< orphan*/  printk_tick () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int printk_needs_cpu(int cpu)
{
	if (unlikely(cpu_is_offline(cpu)))
		printk_tick();
	return per_cpu(printk_pending, cpu);
}