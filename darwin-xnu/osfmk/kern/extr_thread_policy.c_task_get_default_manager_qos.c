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
typedef  int /*<<< orphan*/  task_t ;

/* Variables and functions */
 int THREAD_QOS_LEGACY ; 
 int THREAD_QOS_USER_INITIATED ; 
 int task_compute_main_thread_qos (int /*<<< orphan*/ ) ; 

int
task_get_default_manager_qos(task_t task)
{
	int primordial_qos = task_compute_main_thread_qos(task);

	if (primordial_qos == THREAD_QOS_LEGACY)
		primordial_qos = THREAD_QOS_USER_INITIATED;

	return primordial_qos;
}