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
typedef  int /*<<< orphan*/ * timer_call_t ;
typedef  int /*<<< orphan*/  spl_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_warm_call_list ; 
 int /*<<< orphan*/  cpu_warm_lock ; 
 scalar_t__ dequeue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static timer_call_t
grab_warm_timer_call()
{
	spl_t x;
	timer_call_t call = NULL;

	x = splsched();
	simple_lock(&cpu_warm_lock);
	if (!queue_empty(&cpu_warm_call_list)) {
		call = (timer_call_t) dequeue_head(&cpu_warm_call_list);
	}
	simple_unlock(&cpu_warm_lock);
	splx(x);

	return call;
}