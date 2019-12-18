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
 int _map_to_cpu (unsigned int) ; 
 int /*<<< orphan*/  cpu_map_lock ; 
 int /*<<< orphan*/  cpu_online (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

int map_to_cpu(unsigned int index)
{
	int mapped_cpu;
	unsigned long flag;

	spin_lock_irqsave(&cpu_map_lock, flag);
	mapped_cpu = _map_to_cpu(index);

#ifdef CONFIG_HOTPLUG_CPU
	while (unlikely(!cpu_online(mapped_cpu)))
		mapped_cpu = _map_to_cpu(index);
#endif
	spin_unlock_irqrestore(&cpu_map_lock, flag);
	return mapped_cpu;
}