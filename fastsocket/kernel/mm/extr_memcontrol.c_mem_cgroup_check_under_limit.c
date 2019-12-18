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
struct mem_cgroup {int /*<<< orphan*/  res; int /*<<< orphan*/  memsw; } ;

/* Variables and functions */
 scalar_t__ do_swap_account ; 
 scalar_t__ res_counter_check_under_limit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool mem_cgroup_check_under_limit(struct mem_cgroup *mem)
{
	if (do_swap_account) {
		if (res_counter_check_under_limit(&mem->res) &&
			res_counter_check_under_limit(&mem->memsw))
			return true;
	} else
		if (res_counter_check_under_limit(&mem->res))
			return true;
	return false;
}