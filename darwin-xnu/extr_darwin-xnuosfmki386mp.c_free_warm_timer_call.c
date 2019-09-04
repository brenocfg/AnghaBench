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
typedef  scalar_t__ timer_call_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  queue_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_warm_call_list ; 
 int /*<<< orphan*/  cpu_warm_lock ; 
 int /*<<< orphan*/  enqueue_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_warm_timer_call(timer_call_t call)
{
	spl_t x;

	x = splsched();
	simple_lock(&cpu_warm_lock);
	enqueue_head(&cpu_warm_call_list, (queue_entry_t)call);
	simple_unlock(&cpu_warm_lock);
	splx(x);
}