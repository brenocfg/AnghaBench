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
typedef  int /*<<< orphan*/  queue_entry_t ;

/* Variables and functions */
 int NUM_CPU_WARM_CALLS ; 
 int /*<<< orphan*/ * cpu_warm_call_arr ; 
 int /*<<< orphan*/  cpu_warm_call_list ; 
 int /*<<< orphan*/  cpu_warm_lock ; 
 int /*<<< orphan*/  enqueue_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cpu_prewarm_init()
{
	int i;

	simple_lock_init(&cpu_warm_lock, 0);
	queue_init(&cpu_warm_call_list);
	for (i = 0; i < NUM_CPU_WARM_CALLS; i++) {
		enqueue_head(&cpu_warm_call_list, (queue_entry_t)&cpu_warm_call_arr[i]);
	}
}