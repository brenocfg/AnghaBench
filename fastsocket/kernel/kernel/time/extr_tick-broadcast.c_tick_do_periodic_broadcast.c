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
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tick_broadcast_lock ; 
 int /*<<< orphan*/  tick_do_broadcast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tick_get_broadcast_mask () ; 
 int /*<<< orphan*/  tmpmask ; 
 int /*<<< orphan*/  to_cpumask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tick_do_periodic_broadcast(void)
{
	spin_lock(&tick_broadcast_lock);

	cpumask_and(to_cpumask(tmpmask),
		    cpu_online_mask, tick_get_broadcast_mask());
	tick_do_broadcast(to_cpumask(tmpmask));

	spin_unlock(&tick_broadcast_lock);
}