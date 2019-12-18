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
 int /*<<< orphan*/  cgroup_queue_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rebuild_sched_domains_work ; 

__attribute__((used)) static void async_rebuild_sched_domains(void)
{
	cgroup_queue_work(&rebuild_sched_domains_work);
}