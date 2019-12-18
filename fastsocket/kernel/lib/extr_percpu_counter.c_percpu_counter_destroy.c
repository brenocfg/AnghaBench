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
struct percpu_counter {int /*<<< orphan*/ * counters; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_counters_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void percpu_counter_destroy(struct percpu_counter *fbc)
{
	if (!fbc->counters)
		return;

#ifdef CONFIG_HOTPLUG_CPU
	spin_lock(&percpu_counters_lock);
	list_del(&fbc->list);
	spin_unlock(&percpu_counters_lock);
#endif
	free_percpu(fbc->counters);
	fbc->counters = NULL;
}