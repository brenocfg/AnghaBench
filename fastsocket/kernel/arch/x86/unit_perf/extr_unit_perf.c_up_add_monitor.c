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
struct unit_perf_monitor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_up_monitor ; 
 int /*<<< orphan*/  insert_monitor (struct unit_perf_monitor*,char const*) ; 
 struct unit_perf_monitor* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int up_add_monitor(const char *name)
{
	struct unit_perf_monitor *monitor;

	rcu_read_lock();
	monitor = rcu_dereference(g_up_monitor);
	if (monitor) {
		insert_monitor(monitor, name);
	}
	
	rcu_read_unlock();

	return 0;
}