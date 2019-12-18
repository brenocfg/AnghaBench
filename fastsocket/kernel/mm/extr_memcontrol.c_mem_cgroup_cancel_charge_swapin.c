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
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  mem_cgroup_cancel_charge (struct mem_cgroup*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mem_cgroup_disabled () ; 

void mem_cgroup_cancel_charge_swapin(struct mem_cgroup *mem)
{
	if (mem_cgroup_disabled())
		return;
	if (!mem)
		return;
	mem_cgroup_cancel_charge(mem, PAGE_SIZE, 1);
}