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

/* Variables and functions */
 int /*<<< orphan*/  lb_thread_lock ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tracker_thread_lock ; 
 int /*<<< orphan*/  wait_for_work_threads_exit () ; 

int tracker_service_destroy()
{
	wait_for_work_threads_exit();
	pthread_mutex_destroy(&tracker_thread_lock);
	pthread_mutex_destroy(&lb_thread_lock);

	return 0;
}