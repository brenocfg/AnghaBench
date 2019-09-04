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
typedef  int /*<<< orphan*/  thread_t ;

/* Variables and functions */
 scalar_t__ kpc_threads_counting ; 
 int /*<<< orphan*/  kpc_update_thread_counters (int /*<<< orphan*/ ) ; 

void
kpc_off_cpu_internal(thread_t thread)
{
	if (kpc_threads_counting) {
		kpc_update_thread_counters(thread);
	}
}