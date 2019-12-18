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
struct mem_cgroup {int /*<<< orphan*/  under_oom; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcg_wakeup_oom (struct mem_cgroup*) ; 

__attribute__((used)) static void memcg_oom_recover(struct mem_cgroup *mem)
{
	if (mem && atomic_read(&mem->under_oom))
		memcg_wakeup_oom(mem);
}