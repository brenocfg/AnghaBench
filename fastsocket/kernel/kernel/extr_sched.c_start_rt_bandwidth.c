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
struct rt_bandwidth {scalar_t__ rt_runtime; int /*<<< orphan*/  rt_runtime_lock; int /*<<< orphan*/  rt_period; int /*<<< orphan*/  rt_period_timer; } ;

/* Variables and functions */
 scalar_t__ RUNTIME_INF ; 
 scalar_t__ hrtimer_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_bandwidth_enabled () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_bandwidth_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_rt_bandwidth(struct rt_bandwidth *rt_b)
{
	if (!rt_bandwidth_enabled() || rt_b->rt_runtime == RUNTIME_INF)
		return;

	if (hrtimer_active(&rt_b->rt_period_timer))
		return;

	spin_lock(&rt_b->rt_runtime_lock);
	start_bandwidth_timer(&rt_b->rt_period_timer, rt_b->rt_period);
	spin_unlock(&rt_b->rt_runtime_lock);
}