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
 int /*<<< orphan*/  TASK_NORMAL ; 
 int /*<<< orphan*/  __wake_up (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mem_cgroup*) ; 
 int /*<<< orphan*/  memcg_oom_waitq ; 

__attribute__((used)) static void memcg_wakeup_oom(struct mem_cgroup *mem)
{
	/* for filtering, pass "mem" as argument. */
	__wake_up(&memcg_oom_waitq, TASK_NORMAL, 0, mem);
}