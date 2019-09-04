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
typedef  int /*<<< orphan*/  spl_t ;

/* Variables and functions */
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_update_qos_cpu_time_locked (int /*<<< orphan*/ ) ; 

void
thread_update_qos_cpu_time(thread_t thread)
{
	thread_mtx_lock(thread);

	spl_t s = splsched();
	thread_lock(thread);

	thread_update_qos_cpu_time_locked(thread);

	thread_unlock(thread);
	splx(s);

	thread_mtx_unlock(thread);
}